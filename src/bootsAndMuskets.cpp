#include <raylib.h>
#include "raymath.h"
#include <rcamera.h>
#include <iostream>
#include "globals.hpp"
#include "settings.hpp"

struct iVector2D{
    int x;
    int y;
};

iVector2D CarToIso(iVector2D pos);

struct Chunk{
    int** tiles;
    iVector2D position = {0,0};

    const unsigned int chunkSize = 16;
    void DrawChunk(Texture2D& tx0);
    Chunk();
    ~Chunk();
};

Chunk::Chunk(){
    this->tiles = new int*[this->chunkSize];
    for(int i = 0; i < this->chunkSize; i++){
        this->tiles[i] = new int[this->chunkSize];
        for(int j = 0; j < this->chunkSize; j++){
            this->tiles[i][j] = 0;
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
            switch (this->tiles[i][j]){
            case 0:
                DrawTexture(tx0, CarToIso({i + (this->position.x * 16), j + (this->position.y * 16)}).x, CarToIso({i + (this->position.x * 16), j + (this->position.y * 16)}).y, WHITE);
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
            iVector2D topLeft     = CarToIso({chunk.position.x * 16,         chunk.position.y * 16});
            iVector2D topRight    = CarToIso({chunk.position.x * 16 + 15,    chunk.position.y * 16});
            iVector2D bottomLeft  = CarToIso({chunk.position.x * 16,         chunk.position.y * 16 + 15});
            iVector2D bottomRight = CarToIso({chunk.position.x * 16 + 15,    chunk.position.y * 16 + 15});

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

            if (!CheckCollisionRecs(chunkRect, screenSpace)) continue;

            chunk.DrawChunk(tx0);
        }
    }
}



int main() {
    
    InitSettings();

    InitWindow(SETTINGS.game.WIDTH, SETTINGS.game.HEIGHT, "Boots and Muskets --- 0.0.1");
    InitAudioDevice();

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    Region TestMap(256);
    Texture2D Water = LoadTexture("textures/white.png");

    SetTargetFPS(SETTINGS.game.TARGET_FPS);
    SetExitKey(SETTINGS.keybinds.GAME_CLOSE);

    while (!WindowShouldClose()){

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);
            camera.target = Vector2Add(camera.target, delta);
        }
        float wheel = GetMouseWheelMove();
        if (wheel != 0){
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

            // Set the offset to where the mouse is
            camera.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point 
            // under the cursor to the screen space point under the cursor at any zoom
            camera.target = mouseWorldPos;

            // Zoom increment
            float scaleFactor = 1.0f + (0.25f*fabsf(wheel));
            if (wheel < 0) scaleFactor = 1.0f/scaleFactor;
                camera.zoom = Clamp(camera.zoom*scaleFactor, 0.125f, 4.0f);
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(camera);
                TestMap.DrawRegion(Water, camera);
            EndMode2D();
            if (SETTINGS.game.SHOW_FPS)
                DrawFPS(0, 0);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

iVector2D CarToIso(iVector2D pos){
    iVector2D result;

    result.x = pos.x*32 + pos.y*32;
    result.y = (pos.y*32 - pos.x*32) / 2.0f;

    return result; 
} 