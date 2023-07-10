#pragma once
#ifndef TILE_LEVEL_H
#define TILE_LEVEL_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include <iostream>

class TileLevel {
public:
    TileLevel(int screenWidth, int screenHeight);
    ~TileLevel();

    bool loadLevelData();
    bool loadLevelTextures(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);

private:
    std::vector<std::vector<int>> tiles;
    std::vector<SDL_Texture*> tileTextures;
    int tileSize;
};

#endif