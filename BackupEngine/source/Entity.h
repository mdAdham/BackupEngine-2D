#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
protected:
	sf::RectangleShape _hitBox;
	sf::Sprite _shape;
	sf::Vector2f _position;
	bool _hasTexture = false;

public:
	Entity()
	{

	}

	virtual ~Entity() 
	{

	}
	
	virtual void InitEntity() { }
	virtual void Update();
	virtual void Render(sf::RenderWindow& window);
};