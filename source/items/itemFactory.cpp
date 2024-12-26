#include <engine/engine.hpp>
#include <graphics/types/texture.hpp>
#include <nlohmann/json.hpp>
#include <utility/file.hpp>
#include <iostream>
#include <error.hpp>
#include <items/jsonItems.hpp>

namespace Engine {
void
Engine::createItems() {

    const auto folders = Utility::getFolders("items/");
    for (const auto& folder : folders) {
        // Now we fetch all the files inside that folder that match the criteria
        const auto files = Utility::getFiles(folder.string(), ".json");
        // Load all the files
        for (const auto& file : files) {
            const auto content = Utility::getFileContent(file.string());
            try{
                const auto item = nlohmann::json::parse(content)[nlohmann::json::json_pointer("/Data")].get<Items::typeItemJSON>();
                ASSERT_WITH_MESSAGE(mItems.find(static_cast<Items::Id>(item.Id)) != mItems.end(), "Item exist");
                //To avoid casting over and over
                const auto id = static_cast<Items::Id>(item.Id);
                mItems[id] = new Items::Item(GET_BASE(item.Graphic), item.Slot, static_cast<uint16_t>(item.Id), item.Stats);
            }catch(const std::exception& e){
                ASSERT_WITH_MESSAGE(false, e.what());
            }

        }
    }
    mInventory->addItem(mItems[Items::Id::GoldenAmulet]);
    mInventory->addItem(mItems[Items::Id::BasicStaff]);
}

}