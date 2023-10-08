#pragma once

#include <BackupEngine.h>

class Sandbox2D : public BackupEngine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(BackupEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(BackupEngine::Event& e) override;
private:
	BackupEngine::OrthographicCameraController m_CameraController;
	BackupEngine::PerspectiveCameraController m_3DCameraController;

	// Temp
	BackupEngine::Ref<BackupEngine::VertexArray> m_SquareVA;
	BackupEngine::Ref<BackupEngine::Shader> m_FlatColorShader;

	BackupEngine::Ref<BackupEngine::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};