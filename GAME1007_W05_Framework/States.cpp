#include "States.h"
#include "StateManager.h"
#include "Engine.h"
#include <iostream>
using namespace std;

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}
map<string, Mix_Chunk*> m_sfx; // Going to hold the Sound Effects
map<string, Mix_Music*> m_music; // Going to hold the Music

//Mix_FreeChunk(m_sfx["Sound1"]);
//Mix_FreeChunk(m_sfx["Sound2"]);
//Mix_FreeMusic(m_music["Music1"]);
//Mix_FreeMusic(m_music["Music2"]);
//m_sfx.clear();

// TITLE STATE
TitleState::TitleState(){}
void TitleState::Enter()
{
	cout << "Entering TitleState!" << endl;
	TitleState::Render();
	m_music.emplace("Music1", Mix_LoadMUS("../Assets/aud/Music1.mp3"));
	Mix_PlayMusic(m_music["Music1"], -1);
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
	cout << "Should Be Rendering Title Screen" << endl;
	State::Render();
}
void TitleState::Exit()
{
	cout << "Exiting TitleState!" << endl;
	Mix_FreeChunk(m_sfx["Sound1"]);
}

// GAME STATE
GameState::GameState(){}

void GameState::Enter()
{
	cout << "Entering GameState!" << endl;
	GameState::Render();
	m_music.emplace("Music2", Mix_LoadMUS("../Assets/aud/Music2.mp3"));
	Mix_VolumeMusic(50); // 0-128.
	Mix_PlayMusic(m_music["Music2"], -1);
	m_sfx.emplace("Sound1", Mix_LoadWAV("../Assets/aud/explosion.wav"));
	m_sfx.emplace("Sound2", Mix_LoadWAV("../Assets/aud/Sound2.wav"));
	m_sfx.emplace("Sound3", Mix_LoadWAV("../Assets/aud/Sound1.wav"));
}

void GameState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
	{
		cout << "Changing To PauseState!" << endl;
		// pause music track
		STMA::PushState(new PauseState());
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_X))
	{
		cout << "Changing To EndState!" << endl;
		STMA::PushState(new LoseState());
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_1))
	{
		Mix_PlayChannel(-1, m_sfx["Sound1"], 0);
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_2))
	{
		Mix_PlayChannel(-1, m_sfx["Sound2"], 0);
	}
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	// Any unique rendering in the Game Screen goes here...
	if (dynamic_cast<GameState*>(STMA::GetStates().back()))
		State::Render();
}

void GameState::Exit()
{
	cout << "Exiting GameState!" << endl;
	Mix_FreeChunk(m_sfx["Sound1"]);
	Mix_FreeChunk(m_sfx["Sound2"]);
	Mix_FreeMusic(m_music["Music2"]);
	m_sfx.clear();
}

void GameState::Resume()
{
	cout << "Resuming GameState!" << endl;
	// Make sure to invoke Mix_FreeMusic;
}


// PAUSE STATE
PauseState::PauseState(){}

void PauseState::Enter()
{
	cout << "Entering PauseState!" << endl;
	PauseState::Render();
	Mix_PausedMusic();
	// Load Music track 2 add it to map
	// and play it
	// Load Sfx tracks add it to map
}

void PauseState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_O))
	{

		cout << "Changing To GameState!" << endl;
		STMA::PopState();
		SDL_RenderClear(Engine::Instance().GetRenderer());
		// play music track again
	}
}

void PauseState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	// Any unique rendering in the Game Screen goes here...
	if (dynamic_cast<GameState*>(STMA::GetStates().back()))
		State::Render();
}

void PauseState::Exit()
{
	Mix_ResumeMusic();
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
	cout << "Exiting Pause State!" << endl;
}

// LOSE STATE
LoseState::LoseState(){}

void LoseState::Enter()
{
	LoseState::Render();
	cout << "Entering GameState!" << endl;
}

void LoseState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
	{
		cout << "Restarting Game!" << endl;
		STMA::ChangeState(new TitleState());
	}
}

void LoseState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	// Any unique rendering in the Game Screen goes here...
	if (dynamic_cast<GameState*>(STMA::GetStates().back()))
		State::Render();
}

void LoseState::Exit()
{

}
