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
protected: // private but inherited
	State() = default;
};


class TitleState : public State
{
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};


class GameState : public State
{
public:
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
};

//class PauseState : public State
//{
//public:
//	PauseState();
//	virtual void Enter();
//	virtual void Update();
//	virtual void Render();
//	virtual void Exit();
//};
//
//class LoseState : public State
//{
//public:
//	LoseState();
//	virtual void Enter();
//	virtual void Update();
//	virtual void Render();
//	virtual void Exit();
//};

#endif

