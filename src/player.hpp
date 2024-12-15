#pragma once
#include <raylib.h>
#include "globals.hpp"
#include "settings.hpp"

class Player {
    public:
    //Physical Attributes Getters
    Vector2 GetPosition();
    Vector2 GetHitBoxSize();
    Vector2 GetSpeed();
    //Kinematic Attributes Getters
    Vector2 GetVelocity();
    Vector2 GetAcceleration();
    //Tint Getter
    Color GetColour();
    //Why are these here Getters
    bool IsOnGround();
    float GetAirTime();
    //Let's call these Timmys
    void Tick();
    void Draw();
    //And these staples of OOP
    Player();
    ~Player();

    private:
    //This crap is private since modders would likely pull off some strange bullshit.
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