#include "tilelevel.h"
#include <fstream>

TileLevel::TileLevel(int screenWidth, int screenHeight)
{
    tileSize = 32;  // Adjust this value according to your tile size

    // Calculate the number of rows and columns for the tiles
    int numCols = screenWidth / tileSize;
    int numRows = screenHeight / tileSize;

    // Resize the tiles vector to match the number of rows and columns
    tiles.resize(numRows, std::vector<int>(numCols, 0));

    // Set the tiles at the borders as barriers (1)
    for (int col = 0; col < numCols; ++col) {
        tiles[0][col] = 0;                           // Top border
        tiles[numRows - 1][col] = 1;                  // Bottom border
    }
    for (int row = 0; row < numRows; ++row) {
        tiles[row][0] = 1;                           // Left border
        tiles[row][numCols - 1] = 0;                 // Right border
    }

    // You can customize these values to design the platform map as you desire

    // Platform 1
    int platform1StartCol = 2;
    int platform1EndCol = 8;
    int platform1Row = numRows - 5;
    for (int col = platform1StartCol; col <= platform1EndCol; ++col) {
        tiles[platform1Row][col] = 2; // Platform tile
    }

    // Platform 2
    int platform2StartCol = 12;
    int platform2EndCol = 18;
    int platform2Row = numRows - 8;
    for (int col = platform2StartCol; col <= platform2EndCol; ++col) {
        tiles[platform2Row][col] = 2; // Platform tile
    }

    // Platform 3
    int platform3StartCol = 22;
    int platform3EndCol = 28;
    int platform3Row = numRows - 11;
    for (int col = platform3StartCol; col <= platform3EndCol; ++col) {
        tiles[platform3Row][col] = 2; // Platform tile
    }

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