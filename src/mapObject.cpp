#include "mapObject.hpp"

MapObject::MapObject(unsigned int mapSize){
    if (mapSize == 0){
        this->isEmpty = true;
        return;
    }

    this->isEmpty = false;
    this->mapTiles.resize(mapSize);
}

MapObject::~MapObject(){
    this->mapTiles.clear();
}

std::vector<TileObject>& MapObject::GetMapTiles(){
    return this->mapTiles;
}