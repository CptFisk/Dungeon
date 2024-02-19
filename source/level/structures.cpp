#include <level/structures.hpp>
#include <cstring>
#include <fstream>

namespace Level{
void writeMapToFile(const std::string& filename, const Map& data){
    std::ofstream file(filename, std::ios::binary);
    if(!file.is_open())
        return;
    //Write header
    file.write(reinterpret_cast<const char*>(&data.Header), sizeof(data.Header));
    //Write meta
    file.write(reinterpret_cast<const char*>(&data.Meta), sizeof(data.Meta));
    //Write tile-data
    const int size = data.Header.MapSizeX * data.Header.MapSizeY;
    for(int i = 0; i < size; i++){
        file.write(reinterpret_cast<const char*>(data.Tiles[i]), sizeof(Level::Tile));
    }
    file.close();
}

Tile** newTile(const int& x, const int& y){
    const int size = x *y;
    Tile** map = new Tile*[x*y];
    for(int i = 0; i < size; i++)
        map[i] = new Tile{};
    return map;
}



void
deleteAsset(const uint8_t& id, Assets* map){
    bool found = false;
    for(int i = 0 ; i < MAP_META_MAX; i++){
        if(found){
            map->Data[i - 1] = map->Data[i];
        } else if(map->Data[i].Id == id){
            found = true;
        }
    }
    if(found){
        // Clear the last element (optional)
        memset(&map->Data[MAP_META_MAX - 1], 0, sizeof(Asset));
    }
}

bool
addAsset(const char* asset, Assets* map){
    int lowest = 0;
    for(int i = 0; i < MAP_META_MAX; i++){
        if(map->Data[i].Id == 0) {
            map->Data[i].Id = ++lowest;
            auto len = strlen(asset);
            strncpy(map->Data[i].Asset, asset, len);
            map->Data[i].Asset[len] = '\0'; //Null-terminate
            return true;
        }else{
            if(map->Data[i].Id > lowest)
                lowest = map->Data[i].Id;
        }
    }
    return false;
}
}