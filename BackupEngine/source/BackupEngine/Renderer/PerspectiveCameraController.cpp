#include "bcpch.h"
#include "PerspectiveCameraController.h"

#include "BackupEngine/Core/Input.h"
#include "BackupEngine/Core/KeyCodes.h"
#include "BackupEngine/Core/MouseCodes.h"

#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace BackupEngine {

	PerspectiveCameraController::PerspectiveCameraController(float fov, float aspectRatio, float nearClip, float farClip)
		:m_FOV(fov),
		 m_AspectRatio(aspectRatio),
		 m_FarClip(farClip),
		 m_nearClip(nearClip),
		 m_Camera(fov, aspectRatio, nearClip, farClip)
	{
		UpdateView();
	}

	void PerspectiveCameraController::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_Camera.SetProjection(m_FOV, m_AspectRatio, m_nearClip, m_FarClip);
	}

	void PerspectiveCameraController::UpdateView()
	{
		// m_Yaw = m_Pitch = 0.0f; // Lock the camera's rotation
		m_Camera.SetPosition(CalculatePosition());

		glm::quat orientation = GetOrientation();
		m_Camera.m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Camera.m_Position) * glm::toMat4(orientation);
		m_Camera.m_ViewMatrix = glm::inverse(m_Camera.m_ViewMatrix);
	}

	std::pair<float, float> PerspectiveCameraController::PanSpeed() const
	{
		float x = std::min(m_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	float PerspectiveCameraController::RotationSpeed() const
	{
		return 0.8f;
	}

	float PerspectiveCameraController::ZoomSpeed() const
	{
		float distance = m_Distance * 0.2f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.0f); // max speed = 100
		return speed;
	}

	void PerspectiveCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(Key::LeftAlt))
		{
			const glm::vec2& mouse{ Input::GetMouseX(), Input::GetMouseY() };
			glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.003f;
			m_InitialMousePosition = mouse;

			if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
				MousePan(delta);
			else if (Input::IsMouseButtonPressed(Mouse::ButtonLeft))
				MouseRotate(delta);
			else if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
				MouseZoom(delta.y);
		}

		UpdateView();
	}
	void PerspectiveCameraController::OnEvent(Event& ev)
	{
		EventDispatcher dispacher(ev);
		dispacher.Dispatch<MouseScrolledEvent>(BC_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
	}

	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& ev)
	{
		float delta = ev.GetXOffset() * 0.01f;
		MouseZoom(delta);
		UpdateView();
		return false;
	}
	void PerspectiveCameraController::MousePan(const glm::vec2& delta)
	{
		auto [xSpeed, ySpeed] = PanSpeed();
		m_FocalPoint += -GetRightDirection() * delta.x * xSpeed * m_Distance;
		m_FocalPoint += -GetUpDirection() * delta.y * ySpeed * m_Distance;
	}
	void PerspectiveCameraController::MouseRotate(const glm::vec2& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * delta.x * RotationSpeed();
		m_Pitch += delta.y * RotationSpeed();
	}
	void PerspectiveCameraController::MouseZoom(float delta)
	{
		m_Distance -= delta * ZoomSpeed();
		if (m_Distance < 1.0f)
		{
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.0f;
		}
	}

	glm::vec3 PerspectiveCameraController::GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	glm::vec3 PerspectiveCameraController::GetRightDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	glm::vec3 PerspectiveCameraController::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}
	glm::quat PerspectiveCameraController::GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}
	glm::vec3 PerspectiveCameraController::CalculatePosition() const
	{
		return m_FocalPoint - GetForwardDirection() * m_Distance;
	}
}