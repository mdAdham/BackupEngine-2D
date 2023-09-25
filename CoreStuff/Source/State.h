#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Core.h"
#include "Timestep.h"
#include <stack>

class State;
class StateStack;

struct StateData
{
	sf::RenderWindow* window = nullptr;
	std::shared_ptr<StateStack> states;
};

enum StateID
{
	DEFAULT_STATE,
	GAME_STATE,
	MAINMENU_STATE
};

class State
{
protected:
	StateData* data = nullptr;

public:
	State(StateData* data)
	{
		this->data = data;
	}
	virtual ~State()
	{

	}

	virtual void Update(Timestep ts) = 0;
	virtual void Render() = 0;

	virtual void Pause() { }
	virtual void Resume() { }

};