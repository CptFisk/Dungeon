#include <editor/editor.hpp>
#include <misc/cpp/imgui_stdlib.h>
namespace Editor {

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

            static std::string destX;
            static std::string destY;
            static std::string file;

            ImGui::BeginChild("fileName", ImVec2(300, 0), ImGuiChildFlags_AutoResizeY);
            ImGui::InputText("Filename", &file, ImGuiInputTextFlags_CharsNoBlank);
            ImGui::InputText("X", &destX, ImGuiInputTextFlags_CharsDecimal);
            ImGui::InputText("Y", &destY, ImGuiInputTextFlags_CharsDecimal);
            if (ImGui::Button("Create", ImVec2(300, 0))) {
                Level::File::typeWarpCoordinate origin{ UINT8(coords.first), UINT8(coords.second) }; // Origin
                Level::File::typeWarpCoordinate destination{ UINT8(std::stoi(destX)), UINT8(std::stoi(destY)) };
                fileWarps.emplace_back(Level::File::typeWarpData{origin, destination, file});
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
    /*
if (!clickOnUi(mActionManager->mouseX, mActionManager->mouseY))
    hideElement("WarpsPopup");
     */
}
}