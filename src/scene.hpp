#pragma once
#include <raylib.h>
//Yeah, this IS necessary
#ifdef __GNUC__
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#include "raymath.h"

#ifdef __GNUC__
    #pragma GCC diagnostic pop
#endif
#include <vector>
#include <functional>
#include <bits/stdc++.h> 
#include "sprite.hpp"
#include "globals.hpp"
#include "mapObject.hpp"

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
    MapObject map;

    void CameraInput();

public:
    Scene(SceneType SceneType);
    ~Scene();

    //TODO: Private and implement getter
    unsigned int ID = SCENES;

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


