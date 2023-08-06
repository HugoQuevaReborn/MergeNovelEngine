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
	m_scene = new Scene;
	m_currentPath = std::filesystem::current_path();
	m_application_window = CreateUPointer<Window>();
}

Application::~Application()
{
	delete m_scene;
	SDL_Quit();
}

void Application::Initialize()
{
	__GAME_ASSERT(SDL_Init(SDL_INIT_EVERYTHING));
	__GAME_ASSERT(TTF_Init());
	__GAME_ASSERT(!IMG_Init(IMG_INIT_JPG | IMG_INIT_AVIF | IMG_INIT_PNG | IMG_INIT_WEBP));
	__GAME_ASSERT(!Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC));
	m_application_window->Initialize();
}

const std::filesystem::path& Application::GetCurrentPath()
{
	return m_currentPath;
}

const std::filesystem::path& Application::GetAssetsPath()
{
	return GetCurrentPath() / "assets";
}