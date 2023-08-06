#pragma once
#include <assert.h>
#include <string>
#include <SDL2/SDL.h>
#include <filesystem>
#include <type_traits>
#include "BMemory.h"
#include "defines.h"
#include "../rendering/Window.h"

#define __GAME_ASSERT(x)				(void)((!(x)) ||(_wassert(_CRT_WIDE(#x), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0));
#define __APPLICATION_NAME				"VISUAL NOVEL"

class Window;
class Scene;
class Font;

class Application
{
public:

	Application();
	~Application();

	static Application& Get() { return *m_instance; }
	
	void Initialize();
	Scene* GetScene() { return m_scene; }
	Window* GetWindow() const { return m_application_window.get(); }
	const std::filesystem::path& GetCurrentPath();
	const std::filesystem::path& GetAssetsPath();

private:
	static Application* m_instance;

	bool m_hasAsserted = true;
	std::filesystem::path m_currentPath;
	UPointer<Window> m_application_window;
	Scene* m_scene;
};