#include <editor/editor.hpp>
#include <common/segment.hpp>
#include <imgui.h>
#include <string>
#include <SDL_image.h>

// Internal function to find LCM for animation values
int
findAnimationValue(const std::unordered_map<std::string, int>& data) {
    std::vector<int> temp;
    for (const auto& [asset, value] : data) {
        if (value > 0)
            temp.emplace_back(value);
    }
    return Common::findLcm(temp);
}

namespace Editor {
void
Editor::uiMenu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New project")) {
                fileHeader = File::typeHeaderData{};
                fileAssets.Assets.clear(); // Clear the vector, we start blank
                displayElement("Header");
            }
            if (ImGui::BeginMenu("Load project")) {
                for (const auto& file : mMapFiles) {
                    if (ImGui::MenuItem(file.c_str()))
                        loadLevel(File::readEditorData(file));
                }
                ImGui::EndMenu();
            }
            if(ImGui::MenuItem("Export map", nullptr,nullptr, mMapLoaded)){
                Common::typeSegment segments;
                const auto animationBase = findAnimationValue(animationValuesBase);
                const auto animationTop = findAnimationValue(animationValuesTop);

                //Convert editorTiles to "normal tiles"
                File::typeTiles tiles(editorTiles.size());
                for (int i = 0; i < editorTiles.size(); i++) {
                    tiles.Tiles[i] = editorTiles[i]->getTileData();
                }
                Common::createMap(pRenderer, mGraphics, segments, animationBase, animationTop, tiles, fileAssets);
                for(int i = 0; i < segments.Bottom.Layers.size(); i++){
                    int width, height;
                    SDL_QueryTexture(segments.Bottom.Layers[i], nullptr, nullptr, &width, &height);

                    // Set the texture's blend mode to ensure proper handling of transparency
                    SDL_SetTextureBlendMode(segments.Bottom.Layers[i], SDL_BLENDMODE_BLEND);

                    // Create an SDL_Surface with the same dimensions and RGBA32 format
                    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);

                    if (!surface) {
                        printf("SDL_CreateRGBSurfaceWithFormat failed: %s\n", SDL_GetError());
                        return;
                    }

                    // Set the render target to the texture
                    SDL_SetRenderTarget(pRenderer, segments.Bottom.Layers[i]);

                    // Use SDL_RenderReadPixels to copy the texture's pixel data into the surface
                    if (SDL_RenderReadPixels(pRenderer, nullptr, surface->format->format, surface->pixels, surface->pitch) != 0) {
                        printf("SDL_RenderReadPixels failed: %s\n", SDL_GetError());
                    }

                    // Reset the render target to the default (usually the window)
                    SDL_SetRenderTarget(pRenderer, NULL);

                    // Save the surface as a PNG file with transparency
                    if (IMG_SavePNG(surface, (std::to_string(i) + "file.png").c_str()) != 0) {
                        printf("IMG_SavePNG failed: %s\n", SDL_GetError());
                    }
                    SDL_FreeSurface(surface);
                }
            }
            if (ImGui::MenuItem("Save project")) {

                File::typeTiles tiles(editorTiles.size());
                for (int i = 0; i < editorTiles.size(); i++) {
                    tiles.Tiles[i] = editorTiles[i]->getTileData();
                }

                File::typeEditorFile      map = { fileHeader, fileAssets, tiles, fileDoors, fileWarps };
                const std::string          fileName =
                  UINT8_STRING(fileHeader.MapCoordinate.X) + UINT8_STRING(fileHeader.MapCoordinate.Y) + UINT8_STRING(fileHeader.MapCoordinate.Z);
                File::writeEditorData("levels/" + fileName + ".map", map);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Project", mMapLoaded)) {
            if (ImGui::MenuItem("Level settings")) {
                displayElement("Header");
            }
            if (ImGui::MenuItem("Assets")) {
                displayElement("Assets");
            }
            if (ImGui::MenuItem("On load")) {
                displayElement("OnLoad");
            }
            if (ImGui::MenuItem("On exit")) {
                displayElement("OnExit");
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Display")) {
            if (ImGui::MenuItem("Overlay", nullptr, showOverlay))
                showOverlay = !showOverlay;
            if (ImGui::MenuItem("Numbers", nullptr, showNumbers))
                showNumbers = !showNumbers;
            if (ImGui::MenuItem("Grid", nullptr, showGrid))
                showGrid = !showGrid;
            if (ImGui::MenuItem("Mouse"))
                displayElement("Mouse");
            if (ImGui::MenuItem("Textures"))
                displayElement("Textures");
            if (ImGui::MenuItem("Monster"))
                displayElement("Monster");
            if (ImGui::MenuItem("Doors"))
                displayElement("Doors");
            if (ImGui::MenuItem("Warps"))
                displayElement("Warps");
            ImGui::EndMenu();
        }
        auto status = "Used: " + std::to_string(mLevelCoords.size());
        auto coords = "\tx: " + std::to_string(clickedCoord.first) + " y: " + std::to_string(clickedCoord.second);

        ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize((status + coords).c_str()).x);
        ImGui::Text((status + coords).c_str());
        mWindows["TopMenu"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::EndMainMenuBar();
    }
}
}
