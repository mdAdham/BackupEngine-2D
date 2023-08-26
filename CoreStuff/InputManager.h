#pragma once
#ifdef CORESTUFF_EXPORTS
#define CORESTUFF_API __declspec(dllexport)
#else
#define CORESTUFF_API __declspec(dllimport)
#endif

#include <SFML/Graphics/RenderWindow.hpp>

namespace Utility::Core
{
	struct CORESTUFF_API InputManager
	{
		sf::Vector2i GetMousePosition();
		sf::Vector2i GetMousePosition(sf::RenderWindow& window);
	};
}