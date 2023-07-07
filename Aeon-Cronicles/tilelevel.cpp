#include "tilelevel.h"

TileLevel::TileLevel() {
    tileSize = 32;  // Adjust this value according to your tile size
}

TileLevel::~TileLevel() {}

bool TileLevel::loadLevel(const std::string& filename, SDL_Renderer* renderer) {
    // Load the tile level from the file
    // Parse the file and populate the "tiles" vector with tile IDs
    // Return true if loading is successful, false otherwise
}

void TileLevel::render(SDL_Renderer* renderer) {
    for (int row = 0; row < tiles.size(); ++row) {
        for (int col = 0; col < tiles[row].size(); ++col) {
            int tileID = tiles[row][col];

            // Calculate the position of the current tile
            int x = col * tileSize;
            int y = row * tileSize;

            // Render the tile based on its ID
            // Use SDL_Rect to define the position and size of the tile on the screen
            SDL_Rect tileRect = { x, y, tileSize, tileSize };

            // Example rendering code (change this based on your specific tile representation)
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Set the tile color to white
            SDL_RenderFillRect(renderer, &tileRect);  // Render the tile rectangle
        }
    }
}