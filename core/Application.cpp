#include "Application.h"
#include <filesystem>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_vulkan.h>
#include "../core/Scene.h"
#include "../rendering/Font.h"

Application* Application::m_instance = nullptr;

Application::Application()
{
	m_instance = this;
	m_currentPath = std::filesystem::current_path().string();
	m_scene = new Scene;
	__GAME_ASSERT(Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC) != 0);
	__GAME_ASSERT(!SDL_Init(SDL_INIT_EVERYTHING));
	__GAME_ASSERT(!TTF_Init());
	__GAME_ASSERT(IMG_Init(IMG_INIT_JPG | IMG_INIT_AVIF | IMG_INIT_PNG | IMG_INIT_WEBP));

	SDL_Vulkan_LoadLibrary(nullptr);

	m_application_window = CreateUPointer<Window>();
}

Application::~Application()
{
	delete m_scene;
	SDL_Quit();
}

std::string Application::GetCurrentPath()
{
	return m_currentPath;
}

std::string Application::GetAssetsPath()
{
	return GetCurrentPath() + "\\assets";
}

const char* Application::GetCurrentPathToChar()
{
	return m_currentPath.c_str();
}
