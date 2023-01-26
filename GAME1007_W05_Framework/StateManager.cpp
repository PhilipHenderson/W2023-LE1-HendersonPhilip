#include "StateManager.h"

void StateManager::Update()
{

}

void StateManager::Render()
{

}

void StateManager::PushState(State* pState)
{

}

void StateManager::PopState()
{

}

void StateManager::ChangeState(State* pState)
{

}

void StateManager::Quit()
{

}

std::vector<State*>& StateManager::GetStates()
{
	return s_states;
}

std::vector<State*> StateManager::s_states; 