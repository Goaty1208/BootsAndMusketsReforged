#include "player.hpp"

//PUBLIC ------------------------------------------------------------------------

//Getters -----------------------------------------------------------------------
Vector2 Player::GetPosition(){return this->position;}
Vector2 Player::GetHitBoxSize(){return this->hitBoxSize;}
Vector2 Player::GetSpeed(){return this->speed;}

Vector2 Player::GetVelocity(){return this->velocity;}
Vector2 Player::GetAcceleration(){return this->acceleration;}

Color Player::GetColour(){return this->colour;}

bool Player::IsOnGround(){return this->onGround;}
float Player::GetAirTime(){return this->airtime;}

//Misc -------------------------------------------------------------------------

void Player::Tick(){
    this->GetInput();
    this->UpdatePhysics();
    //Not adding this here would lead to spasms whenever the player lands.
    if (this->position.y >= HEIGHT - this->hitBoxSize.y && !this->onGround) {
        this->velocity.y = 0;
        this->acceleration.y = 0;
        this->position.y = HEIGHT - this->hitBoxSize.y;
        this->onGround = true;
    } 
}

void Player::Draw(){
    //For now the player is 2D
    DrawRectangle(this->position.x, this->position.y, 
                  this->hitBoxSize.x, this->hitBoxSize.y, this->colour);
}

Player::Player(){
    this->position.x = (WIDTH - this->hitBoxSize.x)/2;
}

Player::~Player(){
}

//Private ------------------------------------------------------------------------
//TODO: Write a comment.
void Player::UpdatePhysics(){
    this->velocity.y -= this->acceleration.y * DeltaT; 

    if (this->position.y >= HEIGHT - this->hitBoxSize.y){
        this->onGround = true;
        this->position.y += this->velocity.y + ((this->acceleration.y * DeltaT * DeltaT)/2);
    } else {
        this->position.y += this->velocity.y + ((this->acceleration.y * DeltaT * DeltaT)/2);
        this->acceleration.y += GRAVITY;
        this->onGround = false;
    }
    this->position.x += this->velocity.x * DeltaT;
}
//Input function. It's awful. Too bad!
void Player::GetInput(){
    if (this->onGround && IsKeyPressed(KEY_SPACE)){
        this->velocity.y -= this->speed.y;
    }
    if (IsKeyDown(KEY_A)){
        this->position.x -= this->speed.x;
    }
    if (IsKeyDown(KEY_D)){
         this->position.x += this->speed.x;
    }
}