#include <editor/editor.hpp>
#include <misc/cpp/imgui_stdlib.h>
namespace Editor {

inline std::string
createText(const File::type3DMapCoordinate& level, const File::type2DMapCoordinate& destination) {
    const auto file = "{" + UINT8_STRING(level.X) + "," + UINT8_STRING(level.Y) + "," + UINT8_STRING(level.Z) + "}";
    const auto dest = "[" + UINT8_STRING(destination.X) + "," + UINT8_STRING(destination.Y) + "]";
    return file + "->" + dest;
}

void
Editor::uiWarpsPopup() {
    ImGuiPopupFlags flags       = 0;
    static bool     initialized = false;
    if (mWindowOpen["WarpsPopup"]) {
        ImGui::SetNextWindowPos(popupPosition);
        mMouse = Mouse::DEFAULT;
    }
    ImGui::SetNextWindowSize(ImVec2(200.0f, 0.0f));
    if (ImGui::Begin("Create warp", &mWindowOpen["WarpsPopup"], ImGuiWindowFlags_NoDecoration)) {
        mWindows["WarpsPopup"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        if (ImGui::BeginMenu("Add new")) {
            static std::pair<int, int> coords;
            if (!initialized) {
                const auto x = mActionManager->mouseX;
                const auto y = mActionManager->mouseY;
                coords       = Common::getClickCoords(x + (mOffset.X / -1.0f), y + (mOffset.Y / -1.0f), mScale);
                initialized  = true;
            }
            static std::string fileX;
            static std::string fileY;
            static std::string fileZ;
            static std::string destX;
            static std::string destY;
            ImGui::Text("Level");
            ImGui::InputText("Level X", &fileX, ImGuiInputTextFlags_CharsDecimal);
            ImGui::InputText("Level Y", &fileY, ImGuiInputTextFlags_CharsDecimal);
            ImGui::InputText("Level Z", &fileZ, ImGuiInputTextFlags_CharsDecimal);
            ImGui::Separator();
            ImGui::Text("Destination");
            ImGui::InputText("Destination X", &destX, ImGuiInputTextFlags_CharsDecimal);
            ImGui::InputText("Destination Y", &destY, ImGuiInputTextFlags_CharsDecimal);

            ImGui::BeginChild("fileName", ImVec2(300, 0), ImGuiChildFlags_AutoResizeY);

            if (ImGui::Button("Create", ImVec2(300, 0))) {
                File::type2DMapCoordinate origin{ UINT8(coords.first), UINT8(coords.second) };
                File::type3DMapCoordinate level{ STRING_UINT8(fileX), STRING_UINT8(fileY), STRING_UINT8(fileZ) };
                File::type2DMapCoordinate destination{ STRING_UINT8(destX), STRING_UINT8(destX) };
                fileWarps.emplace_back(File::typeWarpData{ origin, level, destination });
                initialized = false;
                hideElement("WarpsPopup"); // Hide window after mouse click
            }
            ImGui::EndChild();
            ImGui::EndMenu();
        }
        if (ImGui::MenuItem("Abort"))
            hideElement("WarpsPopup");
        ImGui::End();
    }
}

void
Editor::uiWarps() {
    ImGui::SetNextWindowSize(ImVec2(200.0f, 0.0f));
    if (ImGui::Begin("Available warps", &mWindowOpen["Warps"], ImGuiWindowFlags_AlwaysAutoResize)) {
        for (int i = 0; i < fileWarps.size(); i++) {
            auto text = createText(fileWarps[i].Level, fileWarps[i].Destination);
            if (ImGui::BeginMenu(text.c_str())) {
                if (ImGui::MenuItem("Remove"))
                    fileWarps.erase(fileWarps.begin() + i);
                ImGui::EndMenu();
            }
        }
        ImGui::Separator();
        ImGui::End();
    }
}
}