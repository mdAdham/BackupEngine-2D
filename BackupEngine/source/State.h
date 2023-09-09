#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <stack>

class State;

struct StateData
{
	sf::RenderWindow* window = nullptr;
	std::stack<State*> states;
};

enum StateID
{
	GAME_STATE,
	MAINMENU_STATE,
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

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual void Pause() { }
	virtual void Resume() { }

};