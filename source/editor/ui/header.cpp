#include <editor/editor.hpp>
#include <imgui.h>

namespace Editor {

void
Editor::uiHeader(typeWindowCovering& area,bool& open, Level::File::typeHeader& header) {
    static float color[4] = {0.258823544, 0.501960814, 0.866666675, 0}; //Default value for water colour

    ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoAlpha;

    if (ImGui::Begin("Level settings", &open, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::InputScalar("Header version", ImGuiDataType_U8, &header.HeaderVersion);
        ImGui::InputScalar("Map size X", ImGuiDataType_U8, &header.Level.SizeX);
        ImGui::InputScalar("Map size Y", ImGuiDataType_U8, &header.Level.SizeY);
        ImGui::InputText("Level name", header.MapName, IM_ARRAYSIZE(header.MapName));
        ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, nullptr);


        if (ImGui::Button(mNewFile ? "Create" : "Save")) {
            if(mNewFile) {
                mNewFile         = false;
                mMapLoaded       = true;
                const auto sizeX = header.Level.SizeX;
                const auto sizeY = header.Level.SizeY;
                const auto size  = sizeX * sizeY; // Total size

                for (auto& tile : editorTiles) {
                    delete tile;
                }
                editorTiles.clear();
                // Setting up all tiles

                for (int y = 0; y < sizeY; y++) {
                    for (int x = 0; x < sizeX; x++) {
                        // Generating both tiles and visual overlay
                        editorTiles.emplace_back(new Tile(x, y, mScale, *GET_SIMPLE("NumbersWhite"), pRenderer));
                    }
                }
            }else{
                hideElement("Header");
            }

            header.Color.BackgroundRed   = UINT8(FLOAT(color[0] * 255.0f));
            header.Color.BackgroundGreen = UINT8(FLOAT(color[1] * 255.0f));
            header.Color.BackgroundBlue  = UINT8(FLOAT(color[2] * 255.0f));

        }
    }
    area = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
    ImGui::End();

    if (!open)
        hideElement("Header");
}

}