#pragma once
#include <map>
#include "State.h"

namespace BackupEngine {

	class StateStack
	{
	public:
		StateStack(StateID ID, State* default_state);
		~StateStack();
	
		void AddState(StateID ID, State* state);
		void ChangeState(StateID newState);
	
		void Update(Timestep ts);
		void Render();
	private:
		std::map<StateID, State*> m_states;
		StateID activeState = {};
	};

}