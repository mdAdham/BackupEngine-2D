#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "BFileSystem.h"
#include "InputManager.h"
#include "State.h"
#include <stack>
#include <iostream>

struct GameData
{
	Utility::Core::FileSystem::DataFolder* datafolder = nullptr;
	Utility::Core::InputManager input;
	sf::RenderWindow* Window = nullptr;

	/**/
	sf::Event sfEvent{};
};

class DefaultState : public State
{
public:
	DefaultState(StateData* data, GameData& _gamedata)
		:State(data)
	{
		this->gamedata = _gamedata;
		this->m_background_studio_tex.loadFromImage(this->gamedata.datafolder->LoadImageFromFile("texture", "BCS1.data"));
		this->m_background_studio_sprite.setTexture(this->m_background_studio_tex);
		this->m_background_studio_tex.setRepeated(true);
	}

	void Update(float dt) override
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			this->data->window->close();

		std::cout << dt << std::endl;
	}

	void Render() override
	{
		this->data->window->draw(this->m_background_studio_sprite);
	}
private:
	GameData gamedata;
	sf::Texture m_background_studio_tex{};
	sf::Sprite m_background_studio_sprite{};

};

class Application
{
public:
	Application(std::string appName, std::string appDataFolder, sf::Vector2u windowSize);
	~Application();

	void Run();

	void UpdateDt();
	void UpdateSFMLEvents();
	void Update();
	void Render();

private:
	GameData _data;
	DefaultState* state = nullptr;
	std::stack<State*> states;
	bool running = false;
	sf::Clock _dtClock;
	float _dt = 0.f;
	sf::Image appIcon{};
};