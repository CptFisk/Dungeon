#include <level/structures.hpp>
#include <cstring>

namespace Level{
Tile** newTile(const int& x, const int& y){
    const int size = x *y;
    Tile** map = new Tile*[x*y];
    for(int i = 0; i < size; i++)
        map[i] = new Tile{};
    return map;
}

void deleteMapMeta(const uint8_t& id, MapMeta* map){
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
        memset(&map->Data[MAP_META_MAX - 1], 0, sizeof(SubFileMeta));
    }
}

bool addMapMeta(const char* asset, MapMeta* map){
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