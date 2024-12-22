#pragma once
#include <raylib.h>
#include <vector>
#include <fstream>
#include <assert.h>
#include "globals.hpp"

extern std::vector<Texture2D> GameTextures;
extern bool texturesLoaded;

/*
    Loads textures from "texture.txt". The line number of each file name in
    that file is also the ID for that texture.
*/
void LoadTextures();

struct Sprite {
    int spriteID;
    int textureID;
    Vector2 position;

    Sprite(unsigned int textureID, float x, float y){
        this->spriteID = SPRITES;
        SPRITES++;
        this->textureID = textureID; 
        this->position = {x, y};
    }

    void Draw(){
        DrawTexture(GameTextures[this->textureID], 
                    this->position.x, this->position.y, WHITE);
    }
};
