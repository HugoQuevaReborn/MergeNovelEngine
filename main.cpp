#include "core/Application.h"
#include <SDL2/SDL.h>

#define SDL_main main

int main() {
	Application app;
	app.Initialize();

	return 0;
}