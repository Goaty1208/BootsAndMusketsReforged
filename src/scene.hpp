#pragma once
#include <raylib.h>
#include <vector>
#include <functional>
#include <bits/stdc++.h> 
#include "sprite.hpp"
#include "globals.hpp"

enum SceneType {
    LOADING,
    MENU,
    GAME
};

class Scene{
private:
    std::vector<std::reference_wrapper<Sprite>> sprites;
    std::vector<std::reference_wrapper<Sound>> sounds;
    std::vector<std::reference_wrapper<Music>> music;

    SceneType sceneType;
    Camera2D camera;

public:
    Scene(SceneType SceneType);
    ~Scene();

    void AddSprite(Sprite& sprite);
    void AddSound(Sound& sound);
    void AddMusic(Music& music);

    //TODO: Implement getters
    Camera2D& GetCamera();
    Sprite& GetSprite(unsigned int id);

    void Update();
    void DrawSceneGUI();
    void DrawSceneSprites();
};


