#include <common/initializer/imgui.hpp>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

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

    ImGui_ImplSDL2_InitForSDLRenderer(*pWindow, *pRenderer);
    ImGui_ImplSDLRenderer2_Init(*pRenderer);
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
}

void
ImGuiInitializer::shutdown() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

}