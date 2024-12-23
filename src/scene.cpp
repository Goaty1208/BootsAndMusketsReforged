#include "scene.hpp"

Scene::Scene(SceneType SceneType){
    this->sceneType = SceneType;
    this->camera.offset = {0.0f, 0.0f};
    this->camera.target = {0.0f, 0.0f};
     this->camera.rotation = 0.0f;
    this->camera.zoom = 1.0f;
}

Scene::~Scene(){
}

void Scene::AddSprite(Sprite& sprite){
    this->sprites.emplace_back(sprite);
}

void Scene::AddSound(Sound& sound){
    this->sounds.emplace_back(sound);
}

void Scene::AddMusic(Music& music){
    this->music.emplace_back(music);
}

void Scene::Update(){
    //this->camera.zoom = sin(GetTime());
}

void Scene::DrawSceneGUI(){  
    std::string cameraPos = "X: " + std::to_string(this-> camera.offset.x) + " Y: " + std::to_string(this-> camera.offset.y);
    std::string cameraZoom = "Zoom: " + std::to_string(this-> camera.zoom);
    DrawText(cameraPos.c_str(), 0, 20, 20, WHITE);
    DrawText(cameraZoom.c_str(), 0, 42, 20, WHITE);
}

void Scene::DrawSceneSprites(){  
    for (auto& sprite : this->sprites){
        sprite.get().Draw();
    }
}