#include "Preferences.h"

#include <fstream>
#include <SDL3/SDL.h>

namespace {
    std::string prefsPath() {
        const char* base = SDL_GetBasePath();
        std::string dir = base ? base : "";
        return dir + "preferences.txt";
    }
}

void Preferences::save(const std::array<std::string, 4>& paths) {
    std::ofstream out(prefsPath());
    if (!out) return;
    for (int t = 0; t < 4; t++)
        out << paths[t] << "\n";
}

std::array<std::string, 4> Preferences::load() {
    std::array<std::string, 4> paths;
    std::ifstream in(prefsPath());
    if (!in) return paths;

    std::string line;
    for (int t = 0; t < 4 && std::getline(in, line); t++) {
        while (!line.empty() &&
               (line.back() == '\r' || line.back() == ' ' || line.back() == '\t'))
            line.pop_back();
        paths[t] = line;
    }
    return paths;
}
