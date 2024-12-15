#include "settings.hpp"

Settings SETTINGS;

void InitSettings(){
    std::ifstream settingsFile("settings.json");
    if (!settingsFile) {
        // If the settings file doesn't exist, create a default one. Not doing this WILL lead to crashes.
        std::ofstream newSettingsFile("settings.json");
        json newSettings = SETTINGS;  // Serialize SETTINGS struct to JSON
        newSettingsFile << newSettings.dump(4);  // Pretty-print with 4-space indentation
        newSettingsFile.close();
    } else {
        // Load settings from the JSON file
        json settings;
        settingsFile >> settings;  // Read JSON from the file
        SETTINGS = settings.get<Settings>();  // Deserialize JSON to Settings
    }
}
