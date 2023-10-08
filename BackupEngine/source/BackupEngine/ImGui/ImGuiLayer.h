#pragma once

#include "BackupEngine/Core/Layer.h"

#include "BackupEngine/Events/ApplicationEvent.h"
#include "BackupEngine/Events/KeyEvent.h"
#include "BackupEngine/Events/MouseEvent.h"

namespace BackupEngine {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
	};

}