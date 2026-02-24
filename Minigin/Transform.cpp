#include "Transform.h"

using namespace dae;

void Transform::SetLocalPosition(float x, float y, float z)
{
    m_LocalPosition = { x, y, z };
}

void Transform::SetLocalPosition(const glm::vec3& pos)
{
    m_LocalPosition = pos;
}

void Transform::SetWorldPosition(const glm::vec3& pos)
{
    m_WorldPosition = pos;
}