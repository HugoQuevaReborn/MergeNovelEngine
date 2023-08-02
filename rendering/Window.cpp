#include "Window.h"
#include <iostream>
#include "../core/Application.h"
#include "../core/Timer.h"
#include "../rendering/Texture.h"
#include "../rendering/Font.h"
#include "../core/Scene.h"
#include "../core/Math.h"
#include "../ui/UI.h"

Window::Window() {
	m_window = SDL_CreateWindow(
		__APPLICATION_NAME,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		__WINDOW_WITDH,
		__WINDOW_HEIGHT,
		SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_GRABBED
	);

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
}

float Window::GetFramePerSeconds()
{
	return (1000.0F / Time::GetDelta());
}

float Window::GetLastTick()
{
	return m_lastTick;
}

float Window::GetCurrentTick()
{
	return m_currentTick;
}

int Window::GetTicks()
{
	return SDL_GetTicks();
}

void Window::Initialize()
{
	UI::Initialize();
	SDL_Texture* texture = TextureLoader::LoadTexture("HyperSpeedLogo.png");
	int size = 850;
	Application::Get().GetScene().GetBackground().SetTexture(texture);
	Application::Get().GetScene().GetBackground().position.x = 10;
	Application::Get().GetScene().GetBackground().position.y = 10;
	Application::Get().GetScene().GetBackground().scale.x = size;
	Application::Get().GetScene().GetBackground().scale.y = size;
	loop();
}

/// <summary>
/// Manage the core loop of the Window and handle when quiting the application.
/// </summary>
void Window::loop()
{
	bool shouldClose = false;
	SDL_Event sdl_event;

	m_lastTick = 0;
	m_currentTick = SDL_GetPerformanceCounter();
	
	while (!shouldClose) {
		m_frameStart = GetTicks();
		if (m_frameStart > (m_frameStart + 1000)) {
			m_frameTime = m_frameStart;
		}

		SDL_PollEvent(&sdl_event);
		
		switch (sdl_event.type) {
			case SDL_QUIT:
				shouldClose = true;
				break;
			case SDL_WINDOWEVENT:
				if (sdl_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
					UI::Resize(static_cast<float>(sdl_event.window.data1), static_cast<float>(sdl_event.window.data2));
				break;
			case SDL_MOUSEWHEEL:
				mouse_wheel = static_cast<int>(sdl_event.wheel.y);
				break;
			default:
				mouse_wheel = 0;
				break;
		}
		
		update();
		input();
		draw();

		uint32_t m_timerFPS = SDL_GetTicks() - m_frameStart;
		if (m_timerFPS < (1000 / __WINDOW_FPS)) {
			SDL_Delay((1000 / __WINDOW_FPS) - m_timerFPS);
		}
	}
}

void Window::update() {
	mouse_button = SDL_GetMouseState(&mouse_x, &mouse_y);
	m_lastTick = m_currentTick;
	m_currentTick = SDL_GetPerformanceCounter();
}

void Window::input()
{
	
}

void Window::draw()
{
	Application::Get().GetScene().GetBackground().Render();

	UI::Render();
	SDL_RenderPresent(GetRendererInstance());
}

Window::~Window() {
	SDL_DestroyWindow(m_window);
}

SDL_Window* Window::GetWindowInstance()
{
	return m_window;
}

SDL_Renderer* Window::GetRendererInstance() {
	return m_renderer;
}