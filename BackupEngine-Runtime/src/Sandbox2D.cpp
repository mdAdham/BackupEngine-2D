#include "Sandbox2D.h"
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true), m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f }), m_3DCameraController(45.f, 1280.f / 720.f, 0.f, 100.f)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = BackupEngine::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(BackupEngine::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);
	//m_3DCameraController.OnUpdate(ts);

	// Render
	BackupEngine::Renderer2D::ResetStats();
	{
		BackupEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		BackupEngine::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		//BackupEngine::Renderer3D::BeginScene(m_3DCameraController.GetCamera());
		//BackupEngine::Renderer3D::DrawCube(glm::vec3(2.f, 2.f, 5.f), glm::vec3(5.f, 5.f, 5.f), glm::vec4(1.f, 0.86, 0.98, 1.0));
		//BackupEngine::Renderer3D::EndScene();

		BackupEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		BackupEngine::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		BackupEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		BackupEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		BackupEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		BackupEngine::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f);
		BackupEngine::Renderer2D::EndScene();

		BackupEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				BackupEngine::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		BackupEngine::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	auto stats = BackupEngine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(BackupEngine::Event& e)
{
	m_CameraController.OnEvent(e);
	//m_3DCameraController.OnEvent(e);
}
