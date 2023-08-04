#include "Window.h"
#include <iostream>
#include <SDL2/SDL_vulkan.h>
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
	
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	UI::Initialize();
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

void Window::vkInit()
{
	const VkInstanceCreateInfo instInfo = vkCreateInstanceInfo();

	vkCreateInstance(&instInfo, nullptr, &m_vkInstance);

	vkCreateNewDevice();
}

const VkInstanceCreateInfo Window::vkCreateInstanceInfo()
{
	uint32_t extensionCount;
	const char** extensionNames = 0;
	SDL_Vulkan_GetInstanceExtensions(m_window, &extensionCount, nullptr);
	extensionNames = new const char* [extensionCount];
	SDL_Vulkan_GetInstanceExtensions(m_window, &extensionCount, extensionNames);

	return const VkInstanceCreateInfo {
	   VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, // sType
	   nullptr,                                // pNext
	   0,                                      // flags
	   nullptr,                                // pApplicationInfo
	   0,                                      // enabledLayerCount
	   nullptr,                                // ppEnabledLayerNames
	   extensionCount,                         // enabledExtensionCount
	   extensionNames,                         // ppEnabledExtensionNames
	};
}

void Window::vkCreateNewDevice()
{
	uint32_t physicalDeviceCount;
	vkEnumeratePhysicalDevices(m_vkInstance, &physicalDeviceCount, nullptr);
	std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
	vkEnumeratePhysicalDevices(m_vkInstance, &physicalDeviceCount, physicalDevices.data());
	VkPhysicalDevice physicalDevice = physicalDevices[0];

	uint32_t queueFamilyCount;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

	VkSurfaceKHR surface;
	SDL_Vulkan_CreateSurface(m_window, m_vkInstance, &surface);

	uint32_t graphicsQueueIndex = UINT32_MAX;
	uint32_t presentQueueIndex = UINT32_MAX;
	VkBool32 support;
	uint32_t i = 0;

	for (const VkQueueFamilyProperties& queueFamily : queueFamilies) {
		if (graphicsQueueIndex == UINT32_MAX && queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			graphicsQueueIndex = i;
		if (presentQueueIndex == UINT32_MAX) {
			vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &support);
			if (support)
				presentQueueIndex = i;
		}
		++i;
	}

	float queuePriority = 1.0f;
	VkDeviceQueueCreateInfo queueInfo {
		VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, // sType
		nullptr,                                    // pNext
		0,                                          // flags
		graphicsQueueIndex,                         // graphicsQueueIndex
		1,                                          // queueCount
		&queuePriority,                             // pQueuePriorities
	};

	VkPhysicalDeviceFeatures deviceFeatures = {};
	const char* deviceExtensionNames[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	VkDeviceCreateInfo createInfo = {
		VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,   // sType
		nullptr,                                // pNext
		0,                                      // flags
		1,                                      // queueCreateInfoCount
		&queueInfo,                             // pQueueCreateInfos
		0,                                      // enabledLayerCount
		nullptr,                                // ppEnabledLayerNames
		1,                                      // enabledExtensionCount
		deviceExtensionNames,                   // ppEnabledExtensionNames
		&deviceFeatures,                        // pEnabledFeatures
	};

	vkCreateDevice(physicalDevice, &createInfo, nullptr, &m_device);

	VkQueue graphicsQueue;
	vkGetDeviceQueue(m_device, graphicsQueueIndex, 0, &graphicsQueue);

	VkQueue presentQueue;
	vkGetDeviceQueue(m_device, presentQueueIndex, 0, &presentQueue);
}

Window::~Window() {
	vkDestroyDevice(m_device, nullptr);
	vkDestroyInstance(m_vkInstance, nullptr);
	SDL_DestroyWindow(m_window);
	SDL_Vulkan_UnloadLibrary();
}

SDL_Window* Window::GetWindowInstance()
{
	return m_window;
}

SDL_Renderer* Window::GetRendererInstance() {
	return m_renderer;
}