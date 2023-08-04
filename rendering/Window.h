#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vulkan/vulkan.h>

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

	float GetFramePerSeconds();
	float GetLastTick();
	float GetCurrentTick();
	int GetTicks();
	void Initialize();

	int mouse_wheel;
	int mouse_x;
	int mouse_y;
	int mouse_button;
private:

	/// <summary>
	/// Manage the core loop of the Window and handle when quiting the application.
	/// </summary>
	void loop();

	/// <summary>
	/// Gets executed to update every frame.
	/// </summary>
	void update();

	/// <summary>
	/// Gets executed to record the input of the user.
	/// </summary>
	void input();

	/// <summary>
	/// Draw the texture to the screen.
	/// </summary>
	void draw();

	void vkInit();
	void vkCreateNewDevice();
	const VkInstanceCreateInfo vkCreateInstanceInfo();

	const int m_frameDelay = 1000 / __WINDOW_FPS;
	float m_lastTick = 0;
	float m_currentTick = 0;
	uint32_t m_frameStart = 0;
	uint32_t m_frameTime = 0;
	VkDevice m_device;
	VkInstance m_vkInstance;
	
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Surface* m_debugSurface = nullptr;
};