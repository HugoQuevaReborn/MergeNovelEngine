#include "Application.h"
#include <filesystem>
#include <SDL2/SDL_mixer.h>
#include "SDL2/SDL_image.h"
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
	if (!TTF_Init())
		__GAME_ASSERT(1);
	if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_AVIF | IMG_INIT_PNG | IMG_INIT_WEBP))
		__GAME_ASSERT(1);
	
	TTF_Font* default_font_TTF = FontLoader::LoadFont("default_font.ttf",129);
	default_font = new Font();
	default_font->SetFont(default_font_TTF);

	m_application_window = CreateUPointer<Window>();
}

Application::~Application()
{
	delete m_scene;
	delete default_font;
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
