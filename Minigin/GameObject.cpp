#include "GameObject.h"
#include <algorithm>

using namespace dae;

GameObject::GameObject(int priority)
    : m_Priority(priority)
{
}

GameObject::~GameObject() = default;

//
// -----------------------------
// Update / Render
// -----------------------------
//

void GameObject::Update()
{
    if (m_IsDestroyed) return;

    if (m_IsTransformDirty)
        GetWorldPosition();

    for (auto& comp : m_pComponents)
        comp->Update();

    for (auto& child : m_pChildren)
        child->Update();
}

void GameObject::FixedUpdate()
{
    if (m_IsDestroyed) return;

    for (auto& comp : m_pComponents)
        comp->FixedUpdate();

    for (auto& child : m_pChildren)
        child->FixedUpdate();
}

void GameObject::Render() const
{
    if (m_IsDestroyed) return;

    for (const auto& comp : m_pComponents)
        comp->Render();

    for (const auto& child : m_pChildren)
        child->Render();
}

//
// -----------------------------
// Transform
// -----------------------------
//

void GameObject::SetPosition(float x, float y)
{
    m_Transform.SetLocalPosition(x, y);
    SetTransformDirty();
}

glm::vec3 GameObject::GetLocalPosition() const
{
    return m_Transform.GetLocalPosition();
}

glm::vec3 GameObject::GetWorldPosition()
{

    //Only Calculate when Neededed
    if (m_IsTransformDirty)
    {
        if (m_pParent)
        {
            glm::vec3 parentWorld = m_pParent->GetWorldPosition();
            m_Transform.SetWorldPosition(parentWorld + m_Transform.GetLocalPosition());
        }
        else
        {
            m_Transform.SetWorldPosition(m_Transform.GetLocalPosition());
        }

        m_IsTransformDirty = false;
    }

    return m_Transform.GetWorldPosition();
}

void GameObject::SetTransformDirty()
{
    m_IsTransformDirty = true;

    for (auto& child : m_pChildren)
        child->SetTransformDirty();
}

//
// -----------------------------
// Hierarchy
// -----------------------------
//

void GameObject::SetParent(GameObject* pNewParent, bool keepWorldPosition)
{
    if (pNewParent == m_pParent)
        return;

    if (pNewParent == this)
        return;

    if (pNewParent && !pNewParent->CanBeParentOf(this))
        return;

    glm::vec3 worldPos = GetWorldPosition();

    // Remove from old parent
    if (m_pParent)
    {
        auto & siblings = m_pParent->m_pChildren;
        siblings.erase(
            std::remove_if(siblings.begin(), siblings.end(),
                [this](const std::shared_ptr<GameObject>& obj)
                {
                    return obj.get() == this;
                }),
            siblings.end());
    }

    m_pParent = pNewParent;

    if (m_pParent)
    {
        m_pParent->m_pChildren.push_back(shared_from_this());
        m_pParent->SortChildren();
    }

    if (keepWorldPosition)
    {
        if (m_pParent)
        {
            glm::vec3 parentWorld = m_pParent->GetWorldPosition();
            m_Transform.SetLocalPosition(worldPos - parentWorld);
        }
        else
        {
            m_Transform.SetLocalPosition(worldPos);
        }
    }

    SetTransformDirty();
}

void GameObject::AddChild(std::shared_ptr<GameObject> pGameObject, bool keepWorldPosition)
{
    if (!pGameObject) return;

    pGameObject->SetParent(this, keepWorldPosition);
}

void GameObject::RemoveChild(std::shared_ptr<GameObject> pGameObject)
{
    if (!pGameObject) return;

    if (pGameObject->m_pParent != this)
        return;

    pGameObject->SetParent(nullptr, true);
}

GameObject* GameObject::GetParent() const
{
    return m_pParent;
}

bool GameObject::CanBeParentOf(GameObject* pChild) const
{
    if (!pChild) return false;
    if (pChild == this) return false;

    GameObject* current = m_pParent;

    while (current)
    {
        if (current == pChild)
            return false;

        current = current->m_pParent;
    }

    return true;
}

void GameObject::SortChildren()
{
    std::sort(m_pChildren.begin(), m_pChildren.end(),
        [](const std::shared_ptr<GameObject>& a,
            const std::shared_ptr<GameObject>& b)
        {
            return a->GetPriority() < b->GetPriority();
        });
}

//
// -----------------------------
// Components
// -----------------------------
//

void GameObject::AddComponent(std::shared_ptr<Component> pComponent)
{
    if (!pComponent) return;

    pComponent->SetOwner(this);
    m_pComponents.push_back(pComponent);
}

//
// -----------------------------
// Priority / Destruction
// -----------------------------
//

int GameObject::GetPriority() const
{
    return m_Priority;
}

void GameObject::Destroy()
{
    m_IsDestroyed = true;
}

bool GameObject::IsDestroyed() const
{
    return m_IsDestroyed;
}