#include <editor/editor.hpp>

namespace Editor{

void
Editor::uiWarpsPopup() {
    ImGuiPopupFlags flags = 0;

    if (mWindowOpen["WarpsPopup"]) {
        ImGui::SetNextWindowPos(popupPosition);
        mMouse = Mouse::DEFAULT;
    }
    ImGui::SetNextWindowSize(ImVec2(200.0f, 0.0f));
    if (ImGui::Begin("Available doors", &mWindowOpen["WarpsPopup"], ImGuiWindowFlags_NoDecoration)) {

        mWindows["WarpsPopup"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::End();
    }

    if (!clickOnUi(mActionManager->mouseX, mActionManager->mouseY))
        hideElement("WarpsPopup");
}
}