#pragma once
namespace dae
{
	class GameObject;

	class Component
	{
	public:
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();


	  // Components should not be able to change owner.
	  // The default copy and move constructor for a component 
	  // is insufficient.

		Component(const Component&) = delete;
		Component& operator=(const Component&) = delete;
		Component(Component&&) = delete;
		Component& operator=(Component&&) = delete;

		GameObject * GetOwner() const;

		void SetOwner(GameObject* pGameObject);

		bool operator<(const Component& other) const;

		void SetPriority(int priority);
		int GetPriority() const;
	
	protected:
		explicit Component(int priority = 0);

	private:
		GameObject * m_pOwner{ nullptr };
		int m_Priority{ 0 };
	};
}

