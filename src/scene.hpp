#pragma once
#include <raylib.h>
#include <vector>
#include "sprite.hpp"

enum SceneType {
    LOADING,
    MENU,
    GAME
};

class Scene{
private:
    std::vector<Sprite> sprites;
    std::vector<Sound> sounds;
    std::vector<Music> music;

    SceneType sceneType;

public:
    Scene(SceneType SceneType);
    ~Scene();

    void AddSprite(Sprite sprite);
    void GetSprite();

};


