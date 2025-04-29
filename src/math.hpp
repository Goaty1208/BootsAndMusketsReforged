#pragma once 

struct iVector2D{
    int x;
    int y;
};

iVector2D CarToIso(iVector2D pos);


iVector2D CarToIso(iVector2D pos){
    iVector2D result;

    result.x = pos.x*32 + pos.y*32;
    result.y = (pos.y*32 - pos.x*32) / 2.0f;

    return result; 
} 