#pragma once
#ifndef __STATEMANAGER_H__
#define __STATEMANAGER_H__

#include "States.h"
#include <vector>

class StateManager
{ // "Static" class, not a Singlton.
public:
	static void Update();
	static void Render();
	// Spacific StateManager methods:
	static void PushState(State* pState);
	static void PopState();
	static void ChangeState(State* pState);
	static void Quit();
	// Accessor/gettor for states.
	static std::vector<State*>& GetStates();
private:
	StateManager() = default;
	static 	std::vector<State*> s_states;

};

typedef StateManager STMA;
#endif