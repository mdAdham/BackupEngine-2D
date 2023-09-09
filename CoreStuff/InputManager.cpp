#include "pch.h"
#include "InputManager.h"

namespace Utility::Core
{
	sf::Vector2i InputManager::GetMousePosition()
	{
		return sf::Mouse::getPosition();
	}
	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
	{
		return sf::Mouse::getPosition(window);
	}
}