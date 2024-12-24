#include "scene.hpp"

Scene::Scene(SceneType SceneType){
    this->sceneType = SceneType;
    this->camera.offset = {0.0f, 0.0f};
    this->camera.target = {0.0f, 0.0f};
    this->camera.rotation = 0.0f;
    this->camera.zoom = 1.0f;

    //Init Code run only when the scene is first initialised
    switch (this->sceneType){
    case LOADING:
        /* code */
        break;
    case MENU:
        /* code */
        break;
    case GAME:
        /* code */
        break;    
    default:
        break;
    }
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

//Updates ran once per frame
void Scene::Update(){
    switch (this->sceneType){
    case LOADING:
        break;
    case MENU:
        break;
    case GAME:
        this->CameraInput();
        break;    
    default:
        break;
    }
}

Camera2D& Scene::GetCamera(){
    return this->camera;
}

Sprite& Scene::GetSprite(unsigned int id){
    return this->sprites[id].get();
}

void Scene::DrawSceneGUI(){  
    #ifdef DEBUG
        std::string cameraPos = "X: " + std::to_string(this-> camera.offset.x) + " Y: " + std::to_string(this-> camera.offset.y);
        std::string cameraZoom = "Zoom: " + std::to_string(this-> camera.zoom);
        DrawText(cameraPos.c_str(), 0, 20, 20, WHITE);
        DrawText(cameraZoom.c_str(), 0, 42, 20, WHITE);
    #endif
    //Originally this was in the main, but then I realised that that was
    //remarkably stupid and pointless.
    if(SETTINGS.game.SHOW_FPS)
        DrawFPS(0,0);
}

void Scene::DrawSceneSprites(){  
    for (auto& sprite : this->sprites){
        sprite.get().Draw();
    }
}

//User related functions
void Scene::CameraInput(){
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/camera.zoom);
        camera.target = Vector2Add(camera.target, delta);
    }
}