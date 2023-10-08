#include "bcpch.h"
#include "pch.h"
#include "StateStack.h"

namespace BackupEngine {

	StateStack::StateStack(StateID ID, State* default_state)
	{
		this->activeState = ID;
		this->m_states[ID] = default_state;
	}
	
	StateStack::~StateStack()
	{
		this->m_states.clear();
	}
	
	void StateStack::AddState(StateID ID, State* state)
	{
		auto st = this->m_states.find(ID);
		if (st == this->m_states.end())
		{
			this->m_states[ID] = state;
		}
	}
	
	void StateStack::ChangeState(StateID newState)
	{
		auto state = this->m_states.find(newState);
		if (state != this->m_states.end())
		{
			this->activeState = newState;
		}
		else throw("State is not Found!!");
	}
	
	void StateStack::Update(Timestep ts)
	{
		this->m_states[this->activeState]->Update(ts);
	}
	
	void StateStack::Render()
	{
		this->m_states[this->activeState]->Render();
	}
}