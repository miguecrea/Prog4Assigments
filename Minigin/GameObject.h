#pragma once
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <vector>
#include<iostream>
namespace dae
{
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		void Update();
		void FixedUpdate();
		void Render() const;

		GameObject(int priority = 0);
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//Adding child/parent
		void SetParent(GameObject* pGameObject, bool keepWorldPosition = true);
		void AddChild(std::shared_ptr<GameObject> pGameObject, bool keepWorldPosition = true);
		void RemoveChild(std::shared_ptr<GameObject> pGameObject);

		GameObject* GetParent() const;
		bool CanBeParentOf(GameObject* pChild) const;


		void AddComponent(std::shared_ptr<Component> pComponent);


		template<typename Type>
		void RemoveComponent()
		{
			auto it = std::remove_if(m_pComponents.begin(), m_pComponents.end(),
				[](const std::shared_ptr<Component>& component)  //we dont wanna make a copy when passing the shared pointe reven two it goes 
				//outta scope 
				{
					return std::dynamic_pointer_cast<Type>(component) != nullptr;
				});

			if (it != m_pComponents.end())
			{
				m_pComponents.erase(it, m_pComponents.end()); // Safely erase from the vector

				std::cout << "Component eliminated";
			}
			else
			{
				std::cout << "Component was not found";

			}
		}



		template<typename ComponentType>
		std::shared_ptr<ComponentType> GetComponent()
		{
			for (const auto& pComponent : m_pComponents)
			{
				if (auto pTargetComponent = std::dynamic_pointer_cast<ComponentType>(pComponent))
				{
					return pTargetComponent;
				}
			}
			return nullptr;
		}

		template<typename ComponentType>
		bool HasComponentType()
		{
			for (const auto& pComponent : m_pComponents)
			{
				if (auto pTargetComponent = std::dynamic_pointer_cast<ComponentType>(pComponent))
				{
					return true;
				}
			}
			return false;
		}

		//Transform
		void SetPosition(float x, float y);
		glm::vec3 GetWorldPosition();
		glm::vec3 GetLocalPosition() const;

		//Priority
		int GetPriority() const;

		//Destruction
		void Destroy();
		bool IsDestroyed() const;

	private:
		//Child/parent
		std::vector<std::shared_ptr<GameObject>> m_pChildren{};
		GameObject* m_pParent{};
		void SortChildren();

		//Components
		std::vector<std::shared_ptr<Component>> m_pComponents{};

		void SetTransformDirty();

		Transform m_Transform{};
		bool m_IsTransformDirty{ true };

		const int m_Priority{ 0 };

		bool m_IsDestroyed{ false };
	};

}
