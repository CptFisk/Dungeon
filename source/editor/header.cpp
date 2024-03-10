#include <editor/editor.hpp>
#include <imgui.h>

namespace Editor {

void
Editor::uiHeader() {
    static float color[4];

    ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoAlpha;
    if (pLevelHeader == nullptr)
        return;
    if (ImGui::Begin("Level settings", &mWindowOpen["Header"], ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::InputScalar("Header version", ImGuiDataType_U8, &pLevelHeader->HeaderVersion);
        ImGui::InputScalar("Map size X", ImGuiDataType_U8, &pLevelHeader->Level.SizeX);
        ImGui::InputScalar("Map size Y", ImGuiDataType_U8, &pLevelHeader->Level.SizeY);
        ImGui::InputText("Level name", pLevelHeader->MapName, IM_ARRAYSIZE(pLevelHeader->MapName));
        ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, nullptr);

        if (ImGui::Button(mNewFile ? "Create" : "Save")) {
            mNewFile         = false;
            mMapLoaded       = true;
            const auto sizeX = pLevelHeader->Level.SizeX;
            const auto sizeY = pLevelHeader->Level.SizeY;

            pTile           = Level::newTileData(sizeX, sizeY);
            pVisualTile     = newVisualTile(); // Generate a new visual tile
            pVisualTileType = newVisualTileType();

            pLevelHeader->Color.BackgroundRed   = static_cast<float>(color[0] * 255.0f);
            pLevelHeader->Color.BackgroundGreen = static_cast<float>(color[1] * 255.0f);
            pLevelHeader->Color.BackgroundBlue  = static_cast<float>(color[2] * 255.0f);

            // Position for edges
            const auto leftX            = -16.0f * mScale.ScaleX;
            const auto rightX           = 16.0f * mScale.ScaleX * static_cast<float>(sizeX);
            const auto topY             = -16.0f * mScale.ScaleY;
            const auto bottomY          = 16.0f * mScale.ScaleY * static_cast<float>(sizeY);
            const auto tileSizeX        = 16.0f * mScale.ScaleX;
            const auto tileSizeY        = 16.0f * mScale.ScaleY;
            const auto verticalLength   = tileSizeX * (static_cast<float>(sizeY) + 2.0f);
            const auto horizontalLength = tileSizeY * (static_cast<float>(sizeX) + 2.0f);
            // Adding some visuals so we don't paint outside
            mEdges.emplace_back(GET_SDL("FF0000"), SDL_FRect{ leftX, topY, tileSizeX, verticalLength });      // Left
            mEdges.emplace_back(GET_SDL("FF0000"), SDL_FRect{ rightX, topY, tileSizeX, verticalLength });     // Right
            mEdges.emplace_back(GET_SDL("FF0000"), SDL_FRect{ leftX, topY, horizontalLength, tileSizeY });    // top
            mEdges.emplace_back(GET_SDL("FF0000"), SDL_FRect{ leftX, bottomY, horizontalLength, tileSizeY }); // bottom
        }
    }
    mWindows["Header"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
    ImGui::End();

    if (!mWindowOpen["Header"])
        hideElement("Header");
}

}