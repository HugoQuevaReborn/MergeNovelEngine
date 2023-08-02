#pragma once
#include <assert.h>
#include <string>
#include <SDL2/SDL.h>
#include "BMemory.h"
#include "defines.h"
#include "../rendering/Window.h"

#define __GAME_ASSERT(x)			assert(x);
#define __GAME_THROW_EXCEPTION(x)	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "An exception has occured", x, nullptr);
#define __APPLICATION_NAME			"VISUAL NOVEL"

class Window;
class Scene;
class Font;

class Application
{
public:

	Application();
	~Application();

	static Application& Get() { return *m_instance; }

	std::string GetCurrentPath();
	std::string GetAssetsPath();
	const char* GetCurrentPathToChar();
	
	Window& GetWindow() const { return *m_application_window.get(); }
	Scene& GetScene() { return *m_scene; }
	Font* default_font;

private:

	static Application* m_instance;

	bool m_hasAsserted = true;
	std::string m_currentPath;
	UPointer<Window> m_application_window;
	Scene* m_scene;
};