#pragma once
#include "sprite.hpp"

enum TileTypes {
    WATER,
    GRASS
};

struct TileObject{
private:
    TileTypes type;
    Vector2 position;
public:
    TileObject(TileTypes type, float x, float y){
        this->type = type;
        this->position = {x,y};
    };
    ~TileObject();
};