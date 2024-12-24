#pragma once

#include <raylib.h>
#include <nlohmann/json.hpp>
#include <fstream>
using json = nlohmann::json;

struct Keybinds {
    KeyboardKey MOVE_UP = KEY_W;
    KeyboardKey MOVE_DOWN = KEY_S;
    KeyboardKey MOVE_LEFT = KEY_A;
    KeyboardKey MOVE_RIGHT = KEY_D;
    KeyboardKey GAME_CLOSE = KEY_ESCAPE;
    // Automatically define serialisation and deserialisation
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Keybinds, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, GAME_CLOSE)
};

struct Game {
    unsigned int TARGET_FPS = 60;
    unsigned int WIDTH = 800;
    unsigned int HEIGHT = 800;
    #ifdef DEBUG
        bool SHOW_FPS = true;
    #else
        bool SHOW_FPS = false;
    #endif
    // Idem
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Game, TARGET_FPS, WIDTH, HEIGHT, SHOW_FPS)
};

struct Settings {
    Keybinds keybinds;
    Game game;
    // Ibidem
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Settings, keybinds, game)
};

extern Settings SETTINGS;


void InitSettings();