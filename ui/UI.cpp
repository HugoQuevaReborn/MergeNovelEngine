#include "UI.h"
#include "imgui.h"
#include "imgui_sdl.h"
#include "../core/Application.h"
#include "../rendering/Window.h"
#include "../core/Timer.h"

void UI::Initialize()
{
	ImGui::CreateContext();
	ImGuiSDL::Initialize(Application::Get().GetWindow()->GetRendererInstance(), __WINDOW_WITDH, __WINDOW_HEIGHT);
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void UI::Render()
{
	ImGuiIO& io = ImGui::GetIO();

	io.DeltaTime = 1.0F / __WINDOW_FPS;
	io.MousePos = ImVec2(Application::Get().GetWindow()->mouse_x, Application::Get().GetWindow()->mouse_y);
	io.MouseDown[0] = Application::Get().GetWindow()->mouse_button & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = Application::Get().GetWindow()->mouse_button & SDL_BUTTON(SDL_BUTTON_RIGHT);
	io.MouseWheel = Application::Get().GetWindow()->mouse_wheel;

	ImGui::NewFrame();

	{
		ImGui::Begin("DEBUG");
		ImGui::Text("Application Frame Rate");
		ImGui::Text(std::to_string(1000.0F / Time::GetDelta()).c_str());
		ImGui::End();
	}

	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
}

void UI::Clean()
{
	ImGuiSDL::Deinitialize();
	ImGui::DestroyContext();
}

void UI::Resize(float x, float y)
{
	ImGui::GetIO().DisplaySize.x = x;
	ImGui::GetIO().DisplaySize.y = y;
}
