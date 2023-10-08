#pragma once
#include <BackupEngine.h>
#include <BackupEngine/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class SandBox : public BackupEngine::Application
{
public:
	SandBox(const BackupEngine::ApplicationSpecification& specification)
		: BackupEngine::Application(specification)
	{
		PushLayer(new Sandbox2D());
		PushLayer(new ExampleLayer());
	}
};

BackupEngine::Application* BackupEngine::CreateApplication(BackupEngine::ApplicationCommandLineArgs args)
{
	BackupEngine::ApplicationSpecification spec;
	spec.Name = "SandBox";
	spec.WorkingDirectory = "../BackupEngineNut";
	spec.CommandLineArgs = args;

	return new SandBox(spec);
}