#include "tileObject.hpp"

TileObject::TileObject(){
    this->type = WATER;
    this->position = {0,0};
}

TileObject::TileObject(TileTypes type, int x, int y){
    this->type = type;
    this->position = {x,y};
}

TileObject::~TileObject(){

}