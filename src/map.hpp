#pragma once

#include <raylib.h>
#include "raymath.h"
#include <rcamera.h>
#include <iostream>
#include "globals.hpp"
#include "settings.hpp"
#include "math.hpp"

int culled = 0;

struct Tile{
    unsigned short int ID;
    short int depth;
};

struct Chunk{
    Tile** tiles;
    iVector2D position = {0,0};

    const unsigned int chunkSize = 16;
    void DrawChunk(Texture2D& tx0);
    Chunk();
    ~Chunk();
};

Chunk::Chunk(){
    this->tiles = new Tile*[this->chunkSize];
    for(int i = 0; i < this->chunkSize; i++){
        this->tiles[i] = new Tile[this->chunkSize];
        for(int j = 0; j < this->chunkSize; j++){
            this->tiles[i][j].ID = 0;
            this->tiles[i][j].depth = 0;
        }
    }
}

Chunk::~Chunk(){
    for(int i = 0; i < this->chunkSize; i++){
        delete[] this->tiles[i];
    }    
    delete[] this->tiles;
}

void Chunk::DrawChunk(Texture2D& tx0){
    for(int i = 0; i < this->chunkSize; i++){
        for(int j = 0; j < this->chunkSize; j++){
            switch (this->tiles[i][j].ID){
            case 0:
                DrawTexture(tx0, CarToIso({i + (this->position.x * (int) this->chunkSize), j + (this->position.y * (int) this->chunkSize)}).x, CarToIso({i + (this->position.x * (int) this->chunkSize), j + (this->position.y * (int) this->chunkSize)}).y, WHITE);
                break;
            default:
                break; 
            }
        }
    }
}

struct Region{
    Chunk** Chunks;
    unsigned int size; 
    Region(unsigned int size);
    void DrawRegion(Texture2D& tx0, Camera2D& camera);

};

Region::Region(unsigned int size){
    this->size = size;
    this->Chunks = new Chunk*[size];
    for(int i = 0; i < size; i++){
        this->Chunks[i] = new Chunk[size];
        for(int j = 0; j < size; j++){
            this->Chunks[i][j].position = {i, j};
        }
    }
}

void Region::DrawRegion(Texture2D& tx0, Camera2D& camera) {
    Rectangle screenSpace = {
        GetScreenToWorld2D({0, 0}, camera).x,
        GetScreenToWorld2D({0, 0}, camera).y,
        SETTINGS.game.WIDTH / camera.zoom,
        SETTINGS.game.HEIGHT / camera.zoom
    };

    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            Chunk& chunk = this->Chunks[i][j];

            // Get isometric positions of the 4 corners
            iVector2D topLeft     = CarToIso({chunk.position.x * this->Chunks[0][0].chunkSize,                                      chunk.position.y * this->Chunks[0][0].chunkSize});
            iVector2D topRight    = CarToIso({chunk.position.x * this->Chunks[0][0].chunkSize + this->Chunks[0][0].chunkSize -1,    chunk.position.y * this->Chunks[0][0].chunkSize});
            iVector2D bottomLeft  = CarToIso({chunk.position.x * this->Chunks[0][0].chunkSize,                                      chunk.position.y * this->Chunks[0][0].chunkSize + this->Chunks[0][0].chunkSize -1});
            iVector2D bottomRight = CarToIso({chunk.position.x * this->Chunks[0][0].chunkSize + this->Chunks[0][0].chunkSize -1,    chunk.position.y * this->Chunks[0][0].chunkSize + this->Chunks[0][0].chunkSize -1});

            // Find min and max X and Y
            int minX = std::min({topLeft.x, topRight.x, bottomLeft.x, bottomRight.x});
            int maxX = std::max({topLeft.x, topRight.x, bottomLeft.x, bottomRight.x});
            int minY = std::min({topLeft.y, topRight.y, bottomLeft.y, bottomRight.y});
            int maxY = std::max({topLeft.y, topRight.y, bottomLeft.y, bottomRight.y});

            Rectangle chunkRect = {
                (float)minX,
                (float)minY,
                (float)(maxX - minX + 64),  // Add a bit of margin to cover tile width
                (float)(maxY - minY + 32)   // Add a bit of margin to cover tile height
            };

            if (!CheckCollisionRecs(chunkRect, screenSpace)) {
                culled++;
                continue;
            }
            chunk.DrawChunk(tx0);
        }
    }
}


class MapSession{
private:
    /* data */
public:
    MapSession(unsigned int mapSize, bool isNew /*TODO: Implement a save system*/);
    ~MapSession();
};

MapSession::MapSession(unsigned int mapSize, bool isNew /*TODO: Implement a save system*/){
}

MapSession::~MapSession(){
}
