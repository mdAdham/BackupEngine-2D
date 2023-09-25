#pragma once
#include "Core.h"
#include "State.h"
#include "Timestep.h"

#ifdef CORESTUFF_EXPORTS
#define CORESTUFF_API __declspec(dllexport)
#else
#define CORESTUFF_API __declspec(dllimport)
#endif

CORESTUFF_API class StateStack
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
	StateID activeState{};
};
