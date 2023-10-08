#pragma once

#include "PerspectiveCamera.h"

#include "BackupEngine/Core/Timestep.h"
#include "BackupEngine/Events/ApplicationEvent.h"
#include "BackupEngine/Events/MouseEvent.h"

#include <glm/glm.hpp>

namespace BackupEngine {

	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& ev);

		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(float distance) { m_Distance = distance; }

		inline void SetViewportSize(float width, float height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjection(); }

		const glm::mat4 GetViewMatrix() const { return m_Camera.GetViewMatrix(); }
		glm::mat4 GetViewProjection() const { return m_Camera.GetViewProjectionMatrix(); }

		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;
		const glm::vec3& GetPosition() const { return m_Camera.m_Position; }
		glm::quat GetOrientation() const;

		float GetPitich() const { return m_Pitch; }
		float GetYaw() const { return m_Yaw; }

		PerspectiveCamera& GetCamera() { return m_Camera; }
		const PerspectiveCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		void UpdateProjection();
		void UpdateView();

		bool OnMouseScrolled(MouseScrolledEvent& ev);

		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);

		glm::vec3 CalculatePosition() const;

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;

	private:
		float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_nearClip = 0.1f, m_FarClip = 1000.f;
		float m_ZoomLevel = 1.0f;
		PerspectiveCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameroPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };

		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

		float m_Distance = 10.f;
		float m_Pitch = 0.0f, m_Yaw = 0.0f;

		float m_ViewportWidth = 1280, m_ViewportHeight = 720;
	};
}