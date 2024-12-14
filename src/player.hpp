#pragma once
#include <raylib.h>
#include "globals.hpp"

class Player {
    public:

    Vector2 GetPosition();
    Vector2 GetHitBoxSize();
    Vector2 GetSpeed();

    Vector2 GetVelocity();
    Vector2 GetAcceleration();
    
    Color GetColour();

    bool IsOnGround();
    float GetAirTime();

    void Tick();
    void Draw();

    Player();
    ~Player();

    private:

    Vector2 position =     {0.0f, 0.0f};
    Vector2 hitBoxSize =   {50.0f, 120.0f};
    Vector2 speed =        {10.0f, 15.0f};
    
    Vector2 velocity =     {0.0f, 0};
    Vector2 acceleration = { 0.0f, 0.0f };

    Color colour = BLACK;

    bool onGround = false;
    float airtime = 0.0f;

    void UpdatePhysics();
    void GetInput();
};