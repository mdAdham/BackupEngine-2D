#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Base.h"
#include "Timestep.h"
#include <stack>

class State;
class StateStack;

namespace BackupEngine
{

	struct StateData
	{
		sf::RenderWindow* window = nullptr;
		StateStack* states = nullptr;
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
		Ref<StateData> data = nullptr;

	public:
		State(Ref<StateData> data)
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
}