#pragma once

#include "BackupEngine/Core/KeyCodes.h"
#include "BackupEngine/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace BackupEngine {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}