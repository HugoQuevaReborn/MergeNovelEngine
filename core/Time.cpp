#include "Timer.h"
#include "../rendering/Window.h"
#include "../core/Application.h"

float Time::GetDelta()
{
	return ((Application::Get().GetWindow().GetCurrentTick() - Application::Get().GetWindow().GetLastTick()) * 1000 / SDL_GetPerformanceFrequency());
}