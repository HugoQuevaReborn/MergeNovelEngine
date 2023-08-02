#include "core/Application.h"
#include <SDL2/SDL.h>

#define SDL_main main

int main() {
	Application app;
	app.GetWindow().Initialize();

	return 0;
}