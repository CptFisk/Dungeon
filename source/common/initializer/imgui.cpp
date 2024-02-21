#include <common/initializer/imgui.hpp>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>

namespace Common {
ImGuiInitializer::ImGuiInitializer(SDL_Window** window, SDL_Renderer** render)
  : io(ImGui::GetIO())
  , pWindow(window)
  , pRenderer(render) {}

void
ImGuiInitializer::startup() {
    (void)io;

    io.ConfigFlags != ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsLight();

    ImGui_ImplSDL3_InitForSDLRenderer(*pWindow, *pRenderer);
    ImGui_ImplSDLRenderer3_Init(*pRenderer);
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
}

void
ImGuiInitializer::shutdown() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

}