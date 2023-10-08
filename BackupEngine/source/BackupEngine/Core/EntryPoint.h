#pragma once
#include "BackupEngine/Core/Base.h"
#include "BackupEngine/Core/Application.h"

#ifdef EN_PLATFORM_WINDOWS

extern BackupEngine::Application* BackupEngine::CreateApplication(BackupEngine::ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	::BackupEngine::Log::Init();

	//EN_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Startup.json");
	auto app = ::BackupEngine::CreateApplication({ argc, argv });
	//EN_PROFILE_END_SESSION();

	//EN_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
	app->Run();
	//HZ_PROFILE_END_SESSION();

	//EN_PROFILE_BEGIN_SESSION("Shutdown", "HazelProfile-Shutdown.json");
	delete app;
	//EN_PROFILE_END_SESSION();
}

#endif // EN_PLATFORM_WINDOW