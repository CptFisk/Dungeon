#include <level/structures.hpp>
#include <cstring>

namespace Level{
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
}