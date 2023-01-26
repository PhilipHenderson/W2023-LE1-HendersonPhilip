#include "States.h"
#include "StateManager.h"
#include "Engine.h"
#include <iostream>

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

// in a subclass to incoke the render aboce, we just do:
// State::Render();

// TITLE STATE
TitleState::TitleState(){}

void TitleState::Enter()
{
	cout << "Entering TitleState!" << endl;
	// Load Music track add it to map
	// and play it
}

void TitleState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_N))
	{
		cout << "Changing to GameState!" << endl;
		STMA::ChangeState(new GameState());
	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	// Any unique rendering in the Title screen goes here...

	State::Render(); // this invokes SDL_RenderPresent
}

void TitleState::Exit()
{
	cout << "Exiting TitleState!" << endl;
	// Make sure to invoke Mix_FreeMusic;
}

// GAME STATE
GameState::GameState(){}

void GameState::Enter()
{
	cout << "Entering GAMESTATE!" << endl;
	// Load Music track add it to map
	// and play it
}

void GameState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
	{
		cout << "Changing To PauseState!" << endl;
		//STMA::PushState(new PauseState());
	}
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	// Any unique rendering in the Game Screen goes here...
	if (dynamic_cast<GameState*>(STMA::GetStates().back()))
		State::Render(); // this invokes SDL_RenderPresent
}

void GameState::Exit()
{
	cout << "Exiting GameState!" << endl;
	// Make sure to invoke Mix_FreeMusic.
	// Make sure to invoke Mix_FreeChuck. (x2)
}

void GameState::Resume()
{
	cout << "Resuming GameState!" << endl;
	// Make sure to invoke Mix_FreeMusic;
}
//
//
//// PAUSE STATE
//PauseState::PauseState()
//{
//}
//
//void PauseState::Enter()
//{
//}
//
//void PauseState::Update()
//{
//}
//
//void PauseState::Render()
//{
//}
//
//void PauseState::Exit()
//{
//}
//
//// LOSE STATE
//LoseState::LoseState()
//{
//}
//
//void LoseState::Enter()
//{
//}
//
//void LoseState::Update()
//{
//}
//
//void LoseState::Render()
//{
//}
//
//void LoseState::Exit()
//{
//}
