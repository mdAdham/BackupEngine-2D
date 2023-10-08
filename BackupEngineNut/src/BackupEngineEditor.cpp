#include <BackupEngine.h>
#include <BackupEngine/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace BackupEngine {

	class BackupEngineEditor : public Application
	{
	public:
		BackupEngineEditor(const ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new EditorLayer());
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "BackupEngineNut";
		spec.CommandLineArgs = args;

		return new BackupEngineEditor(spec);
	}

}