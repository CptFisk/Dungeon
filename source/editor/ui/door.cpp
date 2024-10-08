#include <common/math.hpp>
#include <editor/editor.hpp>
#include <misc/cpp/imgui_stdlib.h>
#include <string>

namespace Editor {

inline std::string
createText(const File::typeDoorsData& data) {
    const auto x = std::to_string(static_cast<unsigned int>(data.X));
    const auto y = std::to_string(static_cast<unsigned int>(data.Y));
    return "[" + x + "," + y + "]";
}

void
Editor::uiDoor(bool &open) {
    ImGui::SetNextWindowSize(ImVec2(200.0f, 0.0f));
    if (ImGui::Begin("Available doors", &open, ImGuiWindowFlags_AlwaysAutoResize)) {
        for (int i = 0; i < fileDoors.size(); i++) {
            const auto text = createText(fileDoors[i]);
            if (ImGui::BeginMenu(text.c_str())) {
                ImGui::InputText("Condition", &fileDoors[i].Condition);
                if (ImGui::MenuItem("Remove"))
                    fileDoors.erase(fileDoors.begin() + i);
                ImGui::EndMenu();
            }
        }
        ImGui::Separator();
        ImGui::End();
    }
}

void
Editor::uiDoorPopup() {
    if (mWindowOpen["DoorsPopup"]) {
        ImGui::SetNextWindowPos(popupPosition);
        mMouse = Mouse::DEFAULT;
    }
    ImGui::SetNextWindowSize(ImVec2(200.0f, 0.0f));
    if (ImGui::Begin("Create door", &mWindowOpen["DoorsPopup"], ImGuiWindowFlags_NoDecoration)) {
        if (ImGui::MenuItem("Add new")) {
            const auto x      = mActionManager->mouseX;
            const auto y      = mActionManager->mouseY;
            auto       coords = Common::getClickCoords(x + (mOffset.X / -1.0f), y + (mOffset.Y / -1.0f), mScale);
            fileDoors.emplace_back(File::typeDoorsData(coords.first, coords.second, ""));
            hideElement("DoorsPopup"); // Hide window after mouse click
        }
        if (ImGui::MenuItem("Abort"))
            hideElement("DoorsPopup");
        mWindows["DoorsPopup"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::End();
    }

    if (!clickOnUi(mActionManager->mouseX, mActionManager->mouseY))
        hideElement("DoorsPopup");
}

}