#include "bcpch.h"
#include "BackupEngine/Core/Window.h"

#ifdef EN_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif // HZ_PLATFORM_WINDOWS

namespace BackupEngine {

	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef EN_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		BC_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}