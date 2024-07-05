#include <editor/editor.hpp>
#include <imgui.h>
#include <global.hpp>
namespace Editor {

void
Editor::uiHeader(typeWindowCovering& area, bool& open, Level::File::typeHeaderData& header) {
    static float color[4] = { 0.258823544, 0.501960814, 0.866666675, 0 }; // Default value for water colour

    ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoAlpha;

    if (ImGui::Begin("Level settings", &open, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, nullptr);

        if (ImGui::Button(mNewFile ? "Create" : "Save")) {
            if (mNewFile) {
                mNewFile         = false;
                mMapLoaded       = true;

                for (auto& tile : editorTiles) {
                    delete tile;
                }
                editorTiles.clear();
                // Setting up all tiles

                for (int y = 0; y <  MAP_SIZE; y++) {
                    for (int x = 0; x < MAP_SIZE; x++) {
                        // Generating both tiles and visual overlay
                        editorTiles.emplace_back(new Tile(x, y, mScale, *GET_SIMPLE("NumbersWhite"), pRenderer));
                    }
                }
            } else {
                hideElement("Header");
            }

            header.Colour.BackgroundRed   = UINT8(FLOAT(color[0] * 255.0f));
            header.Colour.BackgroundGreen = UINT8(FLOAT(color[1] * 255.0f));
            header.Colour.BackgroundBlue  = UINT8(FLOAT(color[2] * 255.0f));
        }
    }
    area = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
    ImGui::End();

    if (!open)
        hideElement("Header");
}

}