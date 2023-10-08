#pragma once

#include <BackupEngine.h>

class ExampleLayer : public BackupEngine::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(BackupEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(BackupEngine::Event& e) override;
private:
	BackupEngine::ShaderLibrary m_ShaderLibrary;
	BackupEngine::Ref<BackupEngine::Shader> m_Shader;
	BackupEngine::Ref<BackupEngine::VertexArray> m_VertexArray;

	BackupEngine::Ref<BackupEngine::Shader> m_FlatColorShader;
	BackupEngine::Ref<BackupEngine::VertexArray> m_SquareVA;

	BackupEngine::Ref<BackupEngine::Texture2D> m_Texture, m_ChernoLogoTexture;

	BackupEngine::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};