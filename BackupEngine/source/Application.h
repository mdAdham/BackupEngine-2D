#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "BFileSystem.h"
#include "InputManager.h"
#include "StateStack.h"
#include <stack>
#include <iostream>
#include "Timestep.h"

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

	void Update(Timestep ts) override
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			this->data->window->close();

		std::cout << ts << std::endl;
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
	Ref<StateStack> states;
	sf::Clock _dtClock;
	Timestep ts;
	sf::Image appIcon{};
	float m_LastFrameTime = 0.0f;
	bool running = false;
};