#pragma once

#include <glm/glm.hpp>

namespace BackupEngine {

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void SetProjection(float fov, float aspectRatio, float nearClip, float farClip);
		
		const glm::vec3& GetProjection() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; ReCalculateViewMatrix(); }
		
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void ReCalculateViewMatrix();
	public:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
	};

}