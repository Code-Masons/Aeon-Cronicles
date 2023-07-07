#pragma once
#ifndef TILE_LEVEL_H
#define TILE_LEVEL_H

#include <SDL.h>
#include <vector>
#include <string>

class TileLevel {
public:
    TileLevel();
    ~TileLevel();

    bool loadLevel(const std::string& filename, SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);

private:
    std::vector<std::vector<int>> tiles;
    int tileSize;
};

#endif  // TILE_LEVEL_H