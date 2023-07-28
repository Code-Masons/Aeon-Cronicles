#include <iostream>
#include <SDL.h>
#include <chrono>
#include "Game.h"
#include "states.h"
#include "stateManager.h"
#include "Sprite.cpp"
#include "States.cpp"

int main(int argc, char* argv[])
{
	Game& myGameInstance = Game::GetInstance();
	int result = myGameInstance.Init("GAME1017", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	if (result == 0)
	{
		auto lastFrameTime = std::chrono::high_resolution_clock::now();
		while (myGameInstance.IsRunning())
		{
			auto thisFrameTime = std::chrono::high_resolution_clock::now();

			std::chrono::duration<float> lastFrameDurration = thisFrameTime - lastFrameTime;

			float deltaTime = lastFrameDurration.count();

			lastFrameTime = thisFrameTime;

			myGameInstance.HandleEvents();
			myGameInstance.Update(deltaTime);
			myGameInstance.Render();

		}
		myGameInstance.Clean();
	}

	return result;
}