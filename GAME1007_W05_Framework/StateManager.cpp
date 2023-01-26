#include "StateManager.h"

void StateManager::Update()
{
	if (!s_states.empty()) // If the state vector is not empty. (Always)
		s_states.back()->Update(); // Invoke the Update of the "current state"
}

void StateManager::Render()
{
	if (!s_states.empty())
		s_states.back()->Render();

}

void StateManager::PushState(State* pState)
{
	s_states.push_back(pState);
	s_states.back()->Enter();
}

void StateManager::PopState()
{
	//if only one state in vector, return this
	if (s_states.size() <= 1) return;
	if (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}
	s_states.back()->Resume();
}

void StateManager::ChangeState(State* pState)
{
	if (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}
	pState->Enter();
	s_states.push_back(pState);
	/* or:
	* s_states.push_back(pStates)
	* s_states.back()->Enter(); */
}

void StateManager::Quit()
{
	while (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}
}

std::vector<State*>& StateManager::GetStates()
{
	return s_states;
}

std::vector<State*> StateManager::s_states; 