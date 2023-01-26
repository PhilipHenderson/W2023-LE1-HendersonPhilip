#pragma once
#ifndef __STATES_H__
#define __STATES_H__

class State //Abstract base class
{ //  no objects of state can ever be created.
public: 
	virtual void Enter() = 0; // Pure Virtual Function
	virtual void Update() = 0;
	void Render(); // make definiation for render();
	virtual void Exit() = 0;
	void Resume() {};
protected: // priveate but inherited
	State() = default;
};

#endif

