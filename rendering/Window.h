#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define __WINDOW_WITDH	850
#define __WINDOW_HEIGHT	600
#define __WINDOW_FPS 60

class Window
{
public:
	Window();
	~Window();

	SDL_Window* GetWindowInstance();
	SDL_Renderer* GetRendererInstance();

	void Initialize();
	float GetFramePerSeconds();
	float GetLastTick();
	float GetCurrentTick();
	int GetTicks();

	int mouse_wheel = 0;
	int mouse_x = 0;
	int mouse_y = 0;
	int mouse_button = 0;
private:
	void initGL();
	void loop();
	void update();
	void input();
	void draw();

	const int m_frameDelay = 1000 / __WINDOW_FPS;
	float m_lastTick = 0;
	float m_currentTick = 0;
	uint32_t m_frameStart = 0;
	uint32_t m_frameTime = 0;
	SDL_GLContext m_glContext;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Surface* m_debugSurface = nullptr;
};