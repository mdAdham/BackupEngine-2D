#pragma once

#include "BackupEngine/Core/Base.h"
#include "BackupEngine/Core/Timestep.h"
#include "BackupEngine/Events/Event.h"

namespace BackupEngine {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}
		virtual void OnRender() { }

		const std::string& GetName() const { return m_DebugName; }

	private:
		std::string m_DebugName;

	};

}