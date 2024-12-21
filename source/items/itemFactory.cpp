#include <engine/engine.hpp>
#include <graphics/types/texture.hpp>

namespace Engine {
void
Engine::createItems() {
    auto graphic                    = GET_BASE("GoldAmulet");
    mItems[Items::Id::GoldenAmulet] = new Items::Item(graphic, Items::SlotType::Amulet, static_cast<int>(Items::Id::GoldenAmulet));
}

}