#include "States.h"
#include "Engine.h"

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

// in a subclass to incoke the render aboce, we just do:
// State::Render();