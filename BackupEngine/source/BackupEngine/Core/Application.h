#pragma once

#include "BackupEngine/Core/Base.h"

#include "BackupEngine/Core/BFileSystem.h"
#include "BackupEngine/Core/Window.h"
#include "BackupEngine/Core/LayerStack.h"
#include "BackupEngine/Events/Event.h"
#include "BackupEngine/Events/ApplicationEvent.h"

#include "BackupEngine/Core/Timestep.h"

#include "BackupEngine/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace BackupEngine
{
	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			BC_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
		std::string Name = "BackupEngine Application";
		std::string WorkingDirectory = "../BackupEngineNut";
		Ref<Utility::Core::FileSystem::DataFolder> EngineDataFolder = nullptr;
		ApplicationCommandLineArgs CommandLineArgs;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& spec);
		~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return this->m_ImGuiLayer; }

		static Application& Get() { return *s_Instance; }

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		ApplicationSpecification m_Specification;
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	//Defined in Client
	Application* CreateApplication(ApplicationCommandLineArgs args);
}