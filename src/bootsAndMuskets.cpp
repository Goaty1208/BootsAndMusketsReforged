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
                DrawTexture(tx0,i*32 + j*32, (j*32 - i*32) / 2.0f, WHITE);
                break;
            default:
                break;
            }
        }
    }
}

int main() {
    
    InitSettings();

    InitWindow(SETTINGS.game.WIDTH, SETTINGS.game.HEIGHT, "Boots and Muskets --- 0.0.1");
    InitAudioDevice();

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    Chunk TestMap;
    Texture2D Water = LoadTexture("textures/water.png");

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
                camera.zoom = Clamp(camera.zoom*scaleFactor, 0.125f, 64.0f);
            }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(camera);
                TestMap.DrawChunk(Water);
            EndMode2D();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}