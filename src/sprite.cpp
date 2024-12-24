#include "sprite.hpp"

std::vector<Texture2D> GameTextures;
bool texturesLoaded = false;

/*
    Loads textures from "texture.txt". The line number of each file name in
    that file is also the ID for that texture.
*/
void LoadTextures(){
    Texture2D helperTexture;
    std::string fileContents;
    std::string currentTexture;
    std::fstream file;
    const std::string fileLocation = GetWorkingDirectory();

    fileContents = fileLocation + "/textures/textures.txt";
    assert(FileExists(fileContents.c_str()));

    file.open(fileContents);

    for(std::string CurrentToken; std::getline(file, CurrentToken);) {
        currentTexture = fileLocation + "/textures/" + CurrentToken;
        helperTexture = LoadTexture(currentTexture.c_str());
        GameTextures.emplace_back(helperTexture);
    }

    file.close();
}

void UnloadTextures(){
    for (auto i : GameTextures){
        UnloadTexture(i);
    }
}