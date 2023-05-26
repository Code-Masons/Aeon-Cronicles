#include <iostream>
#include "SDL.h"
int main(int argc, char* argv[])
{
	bool gameRunning = true;

	SDL_Window* pWindow;

	pWindow = SDL_CreateWindow("Aeon Cronicles", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 780,0);

	

	while (gameRunning == true)
	{

	}
	std::cout << "world" << std::endl;
	return 0;
}