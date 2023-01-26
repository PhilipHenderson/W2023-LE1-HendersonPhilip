#include "Engine.h"
#include <iostream>
#include <string>
#include "StateManager.h"
using namespace std;

Engine::Engine():m_pWindow(nullptr), m_pRenderer(nullptr), m_isRunning(false)
{
	
}

int Engine::Run()
{
	if (m_isRunning)
	{
		return 1; // 1 arbitrarily means that engine is already running.
	}
	if (Init("LE1-HendersonPhilip-101137744", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, NULL))
	{
		return 2; // 2 arbitrarily means that something went wrong in init.
	}
	while (m_isRunning) // Main game loop. Run while isRunning = true.
	{
		Wake();
		HandleEvents(); // Input
		Update();       // Processing
		Render();       // Output
		if (m_isRunning == true)
			Sleep();
	}
	Clean(); // Deinitialize SDL and free up memory.
	return 0;
}

int Engine::Init(const char* title, const int xPos, const int yPos, 
	const int width, const int height, const int flags)
{
	cout << "Initializing framework..." << endl;
	SDL_Init(SDL_INIT_EVERYTHING);
	m_pWindow = SDL_CreateWindow(title,	xPos, yPos, width, height, flags);
	if (m_pWindow == nullptr)
	{
		cout << "Error during window creation!" << endl;
		return 1;
	}
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
	if (m_pRenderer == nullptr)
	{
		cout << "Error during renderer creation!" << endl;
		return 1;
	}
	if (Mix_Init(MIX_INIT_MP3) != 0)
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048);
		Mix_AllocateChannels(16);

		//Old Way
		//m_pSound1 = Mix_LoadWAV("../Assets/aud/Sound1.wav");
		//m_pSound2 = Mix_LoadWAV("../Assets/aud/Sound2.wav");
		//m_pMusic1 = Mix_LoadMUS("../Assets/aud/Music1.mp3");
		//m_pMusic2 = Mix_LoadMUS("../Assets/aud/Music2.mp3");
		
		// New Way
		m_sfx.emplace("Sound1", Mix_LoadWAV("../Assets/aud/Sound1.wav") );
		m_sfx.emplace("Sound2", Mix_LoadWAV("../Assets/aud/Sound2.wav") );
		m_music.emplace("Music1", Mix_LoadWAV("../Assets/aud/Music1.mp3"));
		m_music.emplace("Music2", Mix_LoadWAV("../Assets/aud/Music2.mp3"));

	}
	else return 1; // Mixer init failed.
	// Initialize SDL sublibraries.
	
	// Example-specific initialization
	//STMA::ChangeState(new TitleState()); // We'll uncomment this later.
	// Initialize rest of framework.
	Mix_VolumeMusic(16); // 0-128.
	Mix_PlayMusic(m_music["Music1"], -1);
	m_fps = 1.0 / (double)FPS; // Converts FPS into a fraction of seconds.
	m_pKeystates = SDL_GetKeyboardState(nullptr);
	lastFrameTime = chrono::high_resolution_clock::now();
	m_isRunning = true; // Start your engine.
	return 0;
}

void Engine::HandleEvents()
{
	cout << "Handling events..." << endl;
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // Pressing 'X' icon in SDL window.
			m_isRunning = false; // Tell Run() we're done.
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.scancode == SDL_SCANCODE_1)
				Mix_PlayChannel(-1, m_sfx["Sound1"], 0);
			if (event.key.keysym.scancode == SDL_SCANCODE_2)
				Mix_PlayChannel(-1, m_sfx["Sound2"], 0);
			break;
		}
	}
}

void Engine::Wake()
{
	thisFrameTime = chrono::high_resolution_clock::now(); // New snapshot of number of seconds.
	lastFrameDuration = thisFrameTime - lastFrameTime;
	deltaTime = lastFrameDuration.count(); // Now we have our deltaTime multiplier.
	lastFrameTime = thisFrameTime;

	m_start = thisFrameTime; // Comment this out to just use deltaTime.
}

bool Engine::KeyDown(SDL_Scancode c)
{
	if (m_pKeystates != nullptr)
	{
		if (m_pKeystates[c] == 1)
			return true;
	}
	return false;
}

SDL_Renderer* Engine::GetRenderer()
{
	return m_pRenderer;
}

Engine& Engine::Instance() // this is the static method.
{
	static Engine instance; // this is the singleton instance of Engine;
	return instance;
}

void Engine::Update()
{
	cout << "Updating frame..." << endl;
	STMA::Update();
}

void Engine::Sleep() 
{
	// Note: Not really better, but you can decide to not limit frameRate and just use deltaTime.
	// Comment all this out to just use deltaTime.
	m_end = chrono::high_resolution_clock::now();
	m_diff = m_end - m_start; // Similar to before, but now chrono and double.
	if (m_diff.count() < m_fps)
		SDL_Delay((Uint32)((m_fps - m_diff.count()) * 1000.0)); // Sleep for number of ms.
}

void Engine::Render()
{
	cout << "Rendering changes..." << endl;
	STMA::Render();
}

void Engine::Clean()
{
	cout << "Cleaning up..." << endl;
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	Mix_CloseAudio();
	//for (auto const& i : m_sfx)
	//{
	//	Mix_FreeChunk(i.second);
	//}
	//for (auto const& i : m_music)
	//{
	//	Mix_FreeMusic(i.second);
	//}
	Mix_FreeChunk(m_sfx["Sound1"]);
	Mix_FreeChunk(m_sfx["Sound2"]);
	Mix_FreeMusic(m_music["Music1"]);
	Mix_FreeMusic(m_music["Music2"]);
	m_sfx.clear();
	Mix_CloseAudio();
	Mix_Quit();
	STMA::Quit();
	SDL_Quit();
}