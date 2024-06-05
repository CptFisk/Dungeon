#include <algorithm>
#include <fstream>
#include <iostream>
#include <level/file.hpp>
#include <stdexcept>

namespace Level::File {
void
writeLevelDataToFile(const std::string& filename, const typeLevelData& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Cant write to file");
    // Write header
    file.write(reinterpret_cast<const char*>(&data.Header), sizeof(data.Header));

    //Write the biggest animated value that we have
    file.write(reinterpret_cast<const char*>(&data.Assets.AnimationValue), sizeof(data.Assets.AnimationValue));

    // Write assets
    const auto numAssets = data.Assets.Assets.size();
    file.write(reinterpret_cast<const char*>(&numAssets), sizeof(numAssets));

    for (const auto& asset : data.Assets.Assets) {
        const auto assetNameLength = static_cast<uint8_t>(asset.size());
        file.write(reinterpret_cast<const char*>(&assetNameLength), sizeof(assetNameLength)); // Write length
        file.write(asset.c_str(), assetNameLength);
    }

    // The tricky part, save tile data
    file.write(reinterpret_cast<const char*>(&data.Tiles.Size), sizeof(data.Tiles.Size));

    for (const auto& tile : data.Tiles.Tiles) {
        // First we write the type
        file.write(reinterpret_cast<const char*>(&tile.Type), sizeof(tile.Type));
        // Write how big the array is
        const auto idLength = static_cast<uint8_t>(tile.Id.size());
        file.write(reinterpret_cast<const char*>(&idLength), sizeof(idLength));
        // Writing all ID:s
        for (const auto id : tile.Id)
            file.write(reinterpret_cast<const char*>(&id), sizeof(id));
    }

    // Write doors to file
    const auto numDoors = data.Doors.Doors.size();
    file.write(reinterpret_cast<const char*>(&numDoors), sizeof(numDoors));

    for (const auto& door : data.Doors.Doors) {
        file.write(reinterpret_cast<const char*>(&door.X), sizeof(door.X));
        file.write(reinterpret_cast<const char*>(&door.Y), sizeof(door.Y));
        const auto open      = static_cast<uint8_t>(door.GraphicOpen.size());
        const auto close     = static_cast<uint8_t>(door.GraphicClosing.size());
        const auto condition = static_cast<uint8_t>(door.Condition.size());
        file.write(reinterpret_cast<const char*>(&open), sizeof(open));
        file.write(door.GraphicOpen.c_str(), open);
        file.write(reinterpret_cast<const char*>(&close), sizeof(close));
        file.write(door.GraphicClosing.c_str(), close);
        file.write(reinterpret_cast<const char*>(&condition), sizeof(condition));
        file.write(door.Condition.c_str(), condition);
    }

    file.close();
}

Level::File::typeLevelData
readLevelData(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        throw std::runtime_error("Cant load file");
    typeHeader header = {};
    typeAssets assets;
    typeDoors  doors;
    // Read size, nothing special here
    file.read(reinterpret_cast<char*>(&header), sizeof(typeHeader));

    file.read(reinterpret_cast<char*>(&assets.AnimationValue), sizeof(assets.AnimationValue));

    // Read the size of how many assets is stored in the file
    size_t numberOfAssets;
    file.read(reinterpret_cast<char*>(&numberOfAssets), sizeof(numberOfAssets));
    for (int i = 0; i < numberOfAssets; i++) {
        uint8_t assetLength = {};
        file.read(reinterpret_cast<char*>(&assetLength), sizeof(assetLength));
        char* assetName = new char[assetLength + 1]{};
        file.read(assetName, assetLength);
        assets.Assets.emplace_back(assetName);
        delete[] assetName; // Clear memory
    }

    uint16_t tileSize;
    file.read(reinterpret_cast<char*>(&tileSize), sizeof(tileSize));

    auto tiles = File::typeTiles(tileSize);
    for (int i = 0; i < tileSize; i++) {
        File::typeTileData tileData;
        file.read(reinterpret_cast<char*>(&tileData), sizeof(tileData.Type));
        uint8_t idSize;
        file.read(reinterpret_cast<char*>(&idSize), sizeof(idSize));
        for (int j = 0; j < idSize; j++) {
            uint8_t id;
            file.read(reinterpret_cast<char*>(&id), sizeof(id));
            tileData.Id.emplace_back(id);
        }
        tiles.Tiles[i] = tileData;
    }

    size_t numberOfDoors;

    file.read(reinterpret_cast<char*>(&numberOfDoors), sizeof(numberOfDoors));
    for(int i = 0; i < numberOfDoors; i++){

        uint8_t x;
        uint8_t y;

        uint8_t  openLength;
        uint8_t  closeLength;
        uint8_t  conditionLength;

        file.read(reinterpret_cast<char*>(&x), sizeof(x));
        file.read(reinterpret_cast<char*>(&y), sizeof(y));

        //Read open animation
        file.read(reinterpret_cast<char*>(&openLength), sizeof(openLength));
        char* openGraphic = new char[openLength + 1]{};
        file.read(openGraphic, openLength);

        //Read close animation
        file.read(reinterpret_cast<char*>(&closeLength), sizeof(closeLength));
        char* closeGraphic = new char[closeLength + 1]{};
        file.read(closeGraphic, closeLength);

        //Read condition
        file.read(reinterpret_cast<char*>(&conditionLength), sizeof(conditionLength));
        char* condition = new char[conditionLength + 1]{};
        file.read(condition, conditionLength);

        doors.Doors.emplace_back(x, y, condition, openGraphic, closeGraphic);
        //Cleanup
        delete[] openGraphic;
        delete[] closeGraphic;
        delete[] condition;

    }


    file.close();
    // Generating response
    return typeLevelData{ header, assets, tiles, doors, typeSpawn() };
}

size_t
addAsset(const std::string& asset, typeAssets& map) {
    const auto size = map.Assets.size();
    map.Assets.emplace_back(asset);
    return size;
}

std::optional<size_t>
findAsset(const std::string& asset, const typeAssets& map) {
    auto it = std::find(map.Assets.begin(), map.Assets.end(), asset);
    if (it != map.Assets.end())
        return std::distance(map.Assets.begin(), it);
    return std::nullopt;
}

bool
removeAsset(const std::string& assetName, typeAssets& map, Level::File::typeTiles& fileTiles) {
    // Calculate our id
    int  assetId;
    bool found = false;
    for (auto it = map.Assets.begin(); it != map.Assets.end(); ++it) {
        if (*it == assetName) {
            assetId = static_cast<int>(std::distance(map.Assets.begin(), it));
            map.Assets.erase(it);
            found = true;
            break; // Stop the loop
        }
    }
    if (!found)
        return false;

    // The asset was found, and we know the ID. Now we have to remove it from the
    for (auto& tile : fileTiles.Tiles) {
        // Loop all the different id's that exist
        for (auto it = tile.Id.begin(); it != tile.Id.end();) {
            if (*it == assetId) {
                it = tile.Id.erase(it);
            } else if (*it > assetId) {
                --(*it);
                ++it;
            } else {
                ++it;
            }
        }
    }
    return true;
}

}