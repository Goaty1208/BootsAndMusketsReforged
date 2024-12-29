#pragma once
#include <vector>
#include <cmath>
#include "tileObject.hpp"
#include "sprite.hpp"
#include "globals.hpp"

class MapObject{
private:
    /*Using a vector since this allows us to keep a map object in each scene even if not needed.
    Since we can resize the vector to hold the map only when we actually need it, the vector can
    either be empty or full, thus saving memory.
    */
    std::vector<TileObject> mapTiles;
    bool isEmpty;
public:
    MapObject(unsigned int mapSize);
    ~MapObject();

    std::vector<TileObject>& GetMapTiles();
};

MapObject::MapObject(unsigned int mapSize){
    if (mapSize == 0){
        this->isEmpty = true;
        return;
    }

    this->isEmpty = false;
    this->mapTiles.resize(mapSize);
}

MapObject::~MapObject(){
}

std::vector<TileObject>& MapObject::GetMapTiles(){
    return this->mapTiles;
}