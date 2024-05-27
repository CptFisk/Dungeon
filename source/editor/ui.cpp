#include <editor/editor.hpp>

namespace Editor{

void
Editor::displayElement(const std::string& element){
    mElementsToShow.push_back(element);
}

void
Editor::hideElement(const std::string& element){
    mElementsToHide.push_back(element);
}

void
Editor::hideAllElements() {
    mHideAllWindows = true;
}

bool Editor::isElementVisible(const std::string& element) {
    return mVisibleElements.find(mElements.find(element)->second) != mVisibleElements.end();
}

bool
Editor::clickOnUi(const int& x, const int& y, const std::string& element) {
    const auto it = mWindows.find(element);
    if(it != mWindows.end())
        if(isOverlap(x, (it)->second.Position.x, (it)->second.Position.x + (it)->second.Size.x) && isOverlap(x, (it)->second.Position.y, (it)->second.Position.y + (it)->second.Size.y))
            return true;
    return false;

}

bool Editor::clickOnUi(const int& x, const int& y) {
    for(const auto&[name, window] : mWindows){
        if(isOverlap(x, window.Position.x, window.Position.x + window.Size.x) &&
            isOverlap(y, window.Position.y, window.Position.y + window.Size.y)){
            return true;
        }
    }
    return false;
}

bool
Editor::isOverlap(const float& value, const float& low, const float& high) {
    return (value < high) && !(value < low) ? true : false;
}

}