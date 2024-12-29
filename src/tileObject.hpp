#pragma once
#include "sprite.hpp"

//TODO: move to a util header
struct IntVector2D{
    int x;
    int y;
};

enum TileTypes {
    WATER,
    GRASS
};

struct TileObject{
private:
    TileTypes type;
    IntVector2D position;
public:
    TileObject(TileTypes type, int x, int y){
        this->type = type;
        this->position = {x,y};
    };
    ~TileObject();
};