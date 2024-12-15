#pragma once

#include <raylib.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct Keybinds {
    KeyboardKey MOVE_JUMP = KEY_W;
    KeyboardKey MOVE_CROUCH = KEY_S;
    KeyboardKey MOVE_LEFT = KEY_A;
    KeyboardKey MOVE_RIGHT = KEY_D;
    KeyboardKey GAME_CLOSE = KEY_ESCAPE;
};

struct Game {
    int TARGET_FPS = 60;
};

struct Settings {
    Keybinds keybinds;
    Game game;
};

extern Settings SETTINGS;