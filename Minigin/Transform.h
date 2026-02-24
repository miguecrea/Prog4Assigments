#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		// --- Getters ---
		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		const glm::vec3& GetWorldPosition() const { return m_WorldPosition; }

		// --- Setters ---
		void SetLocalPosition(float x, float y, float z = 0.f);
		void SetLocalPosition(const glm::vec3& pos);

		void SetWorldPosition(const glm::vec3& pos);

	private:
		glm::vec3 m_LocalPosition{ 0.f, 0.f, 0.f };
		glm::vec3 m_WorldPosition{ 0.f, 0.f, 0.f };
	};
}