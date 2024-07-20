#include <editor/editor.hpp>
#include <editor/utility/mouseLightning.hpp>
namespace Editor {
void
Editor::uiMouseLightning(Editor::Editor::typeWindowCovering& area,
                         bool&                               open,
                         Mouse&                              mouse,
                         LightningShape&                     shape,
                         LightningColour&                    colour,
                         LightningSize&                      size) {
    if (ImGui::Begin("Lightning", &open, ImGuiWindowFlags_AlwaysAutoResize)) {

        ImGui::SeparatorText("Shape");
        mouseButton(shape, LightningShape::LIGHT_SQUARE, "Square");
        mouseButton(shape, LightningShape::LIGHT_CIRCLE, "Circle");

        ImGui::SeparatorText("Colour");
        mouseButton(colour, LightningColour::LIGHT_RED, "Red");
        mouseButton(colour, LightningColour::LIGHT_YELLOW, "Yellow");
        mouseButton(colour, LightningColour::LIGHT_WHITE, "White");
        ImGui::SeparatorText("Size");
        mouseButton(size, LightningSize::LIGHT_SMALL, "Small");
        mouseButton(size, LightningSize::LIGHT_MEDIUM, "Medium");
        mouseButton(size, LightningSize::LIGHT_BIG, "Big");
        area = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::End();
    }

    if (!open) {
        mouse = DEFAULT;
        hideElement("Lightning");
    }
}
}