#include <SDL2/SDL.h>

#include "imgui.h"
#include "imgui_sdl.h"
#include <iostream>

int test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow("SDL2 ImGui Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 3840, 2160, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	ImGui::CreateContext();
	ImGuiSDL::Initialize(renderer, 3840, 2160);
	SDL_RenderSetLogicalSize(renderer, 1920, 1080);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 100, 100);
	{
		SDL_SetRenderTarget(renderer, texture);
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderTarget(renderer, nullptr);
	}

	bool run = true;
	while (run) {
		ImGuiIO& io = ImGui::GetIO();

		int wheel = 0;

		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) run = false;
			else if (e.type == SDL_WINDOWEVENT) {
				if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					io.DisplaySize.x = static_cast<float>(e.window.data1);
					io.DisplaySize.y = static_cast<float>(e.window.data2);
				}
			}
			else if (e.type == SDL_MOUSEWHEEL) {
				wheel = e.wheel.y;
			}
			else if (e.type == SDL_KEYDOWN){
				io.AddInputCharacter(e.key.keysym.sym);
			}
		}
		io.WantCaptureKeyboard = true;

		int mouseX, mouseY;

		const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
		// std::cout << mouseX << " " << mouseY << "\n";

		double factorX = 2;
		double factorY = 2;

		// Setup low-level inputs (e.g. on Win32, GetKeyboardState(), or write to those fields from your Windows message loop handlers, etc.)

		// io.DeltaTime = 1.0f / 60.0f;
		io.MousePos = ImVec2(static_cast<float>(mouseX) / factorX, static_cast<float>(mouseY) / factorY);
		io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
		io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
		io.MouseWheel = static_cast<float>(wheel);
		
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Begin("Image");
		ImGui::Image(texture, ImVec2(100, 100));
		ImGui::End();

		ImGui::Begin("Jaja");
		ImGui::Image(texture, ImVec2(100, 100));
		ImGui::Text("yee");
		ImGui::End();

		SDL_SetRenderDrawColor(renderer, 114, 144, 154, 255);
		SDL_RenderClear(renderer);

		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());

		// SDL_RenderSetLogicalSize(renderer, 360, 240);
		SDL_RenderPresent(renderer);
		// SDL_RenderSetLogicalSize(renderer, 2*777, 2*555);

	}

	ImGuiSDL::Deinitialize();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	ImGui::DestroyContext();

	return 0;
}