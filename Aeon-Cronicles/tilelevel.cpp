#include "tilelevel.h"
#include <fstream>

TileLevel::TileLevel()
{
    tileSize = 32;  // Adjust this value according to your tile size
}

TileLevel::~TileLevel()
{
    for (SDL_Texture* texture : tileTextures)
    {
        SDL_DestroyTexture(texture);
    }
    tileTextures.clear(); // Clear the vector after destroying the textures
}

bool TileLevel::loadLevelData()
{
    std::ifstream file("TileData.txt");
    if (!file.is_open())
    {
        return false;  // Unable to open the file
    }
    else
    {
        std::cout << "Reading data file";
    }

    std::vector<int> row;
    std::string line;

    while (std::getline(file, line))
    {
        row.clear();
        for (char tileID : line)
        {
            row.push_back(tileID - '0');
        }
        tiles.push_back(row);
    }
    file.close();

    return true;
}

bool TileLevel::loadLevelTextures(SDL_Renderer* renderer)
{
    // Load tile textures based on tile IDs
    for (int row = 0; row < tiles.size(); ++row)
    {
        for (int col = 0; col < tiles[row].size(); ++col)
        {
            int tileID = tiles[row][col];
            std::string imagePath = "./assets/terrain.png";

            // Create a texture if it doesn't exist for the tileID
            if (tileID >= tileTextures.size())
            {
                SDL_Surface* surface = IMG_Load(imagePath.c_str());
                if (!surface)
                {
                    // Error loading the image, handle accordingly
                    // You may want to return false here or handle the error in some way
                    return false;
                }

                // Create a texture from the surface
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (!texture)
                {
                    // Error creating texture, handle accordingly
                    SDL_FreeSurface(surface);
                    // You may want to return false here or handle the error in some way
                    return false;
                }

                // Add the texture to the tileTextures vector
                tileTextures.resize(tileID + 1);
                tileTextures[tileID] = texture;

                // Free the surface as it's no longer needed
                SDL_FreeSurface(surface);
            }
        }
    }

    return true;
}

void TileLevel::render(SDL_Renderer* renderer)
{
    // Load tile textures based on tile IDs
    for (int row = 0; row < tiles.size(); ++row)
    {
        for (int col = 0; col < tiles[row].size(); ++col)
        {
            int tileID = tiles[row][col];
            std::string imagePath = "./assets/terrain.png";

            // Create a texture if it doesn't exist for the tileID
            if (tileTextures.size() <= tileID)
            {
                SDL_Surface* surface = IMG_Load(imagePath.c_str());
                if (!surface)
                {
                    // Error loading the image, handle accordingly
                    // You may want to return false here or handle the error in some way
                    return;
                }

                // Create a texture from the surface
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (!texture)
                {
                    // Error creating texture, handle accordingly
                    SDL_FreeSurface(surface);
                    // You may want to return false here or handle the error in some way
                    return;
                }

                // Add the texture to the tileTextures vector
                tileTextures.push_back(texture);

                // Free the surface as it's no longer needed
                SDL_FreeSurface(surface);
            }

            SDL_Texture* texture = tileTextures[tileID];

            int x = col * tileSize;
            int y = row * tileSize;

            SDL_Rect destinationRect = { x, y, tileSize, tileSize };

            SDL_RenderCopy(renderer, texture, nullptr, &destinationRect);
        }
    }
}