#include <editor/editor.hpp>
#include <imgui.h>
#include <global.hpp>
#include <misc/cpp/imgui_stdlib.h>

namespace Editor {

void
Editor::uiHeader(typeWindowCovering& area, bool& open, Level::File::typeHeaderData& header) {
    static std::string dataX = UINT8_STRING(header.MapCoordinate.X);
    static std::string dataY = UINT8_STRING(header.MapCoordinate.Y);
    static std::string dataZ = UINT8_STRING(header.MapCoordinate.Z);

    static float color[4] = { 0.258823544, 0.501960814, 0.866666675, 0 }; // Default value for water colour

    ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoAlpha;

    if (ImGui::Begin("Level settings", &open, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::InputText("X", &dataX, ImGuiInputTextFlags_CharsDecimal);
        ImGui::InputText("Y", &dataY, ImGuiInputTextFlags_CharsDecimal);
        ImGui::InputText("Z", &dataZ, ImGuiInputTextFlags_CharsDecimal);

        ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, nullptr);

        if (ImGui::Button(mNewFile ? "Create" : "Save")) {
            if (!mNewFile) {
                mNewFile         = false;
                mMapLoaded       = true;

                for (auto& tile : editorTiles) {
                    delete tile;
                }
                editorTiles.clear();
                // Setting up all tiles
                for (int y = 0; y < MAP_WIDTH; y++) {
                    for (int x = 0; x < MAP_WIDTH; x++) {
                        // Generating both tiles and visual overlay
                        editorTiles.emplace_back(new Tile(x, y, mScale, *GET_SIMPLE("NumbersWhite"), pRenderer));
                    }
                }
            } else {
                hideElement("Header");
            }
            header.MapCoordinate.X = STRING_UINT8(dataX);
            header.MapCoordinate.Y = STRING_UINT8(dataY);
            header.MapCoordinate.Z = STRING_UINT8(dataZ);
            header.Colour.BackgroundRed   = UINT8(FLOAT(color[0] * 255.0f));
            header.Colour.BackgroundGreen = UINT8(FLOAT(color[1] * 255.0f));
            header.Colour.BackgroundBlue  = UINT8(FLOAT(color[2] * 255.0f));
        }
        area = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::End();
    }

    if (!open)
        hideElement("Header");
}

}