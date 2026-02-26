#include <SDL3/SDL.h>
#include "InputManager.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>

bool dae::InputManager::ProcessInput()
{

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		// 1️⃣ Always give event to ImGui first
		ImGui_ImplSDL3_ProcessEvent(&event);

		if (event.type == SDL_EVENT_QUIT)
			return false;

		if (!ImGui::GetIO().WantCaptureMouse &&
			!ImGui::GetIO().WantCaptureKeyboard)
		{
			// your engine input handling
		}
	}

	return true;





	//SDL_Event e;
	//while (SDL_PollEvent(&e)) {
	//	if (e.type == SDL_EVENT_QUIT) {
	//		return false;
	//	}
	//	if (e.type == SDL_EVENT_KEY_DOWN) {
	//		
	//	}
	//	if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
	//		
	//	}
	//	// etc...
	//}

	//return true;
}
