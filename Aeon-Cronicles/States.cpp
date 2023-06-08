#include <iostream>
#include "States.h"
#include "StateManager.h"
#include "Game.h"

void TitleState::Enter()
{
	std::cout << "entering title state " << std::endl;
}

void TitleState::Update(float deltaTime)
{

	if (Game::GetInstance().KeyDown(SDL_SCANCODE_G))//press g to go to game state
	{
		std::cout << "changing to game state" << std::endl;
		StateManager::ChangeState(new GameState());//change to new game state
	}
}

void TitleState::Render()
{
	std::cout << "rendering title state" << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 255, 0, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void TitleState::Exit()
{
	std::cout << "exiting title state" << std::endl;
}

void GameState::Enter()
{
	std::cout << "entering game state" << std::endl;
}

void GameState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_P))
	{
	std::cout << "changing to pause state" << std::endl;
	StateManager::PushState(new PauseState());
	}
}

void GameState::Render()
{
	std::cout << "rendering game state..." << std::endl;

	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 200, 255);
	SDL_RenderClear(pRenderer);
}

void GameState::Resume()
{
	std::cout << "resuming game state" << std::endl;
}

void GameState::Exit()
{
	std::cout << "exiting game state" << std::endl;
}

void PauseState::Enter()
{
	std::cout << "entering pause state" << std::endl;
}

void PauseState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_R))
	{
		StateManager::popState;
	}
}

void PauseState::Render()
{
	std::cout << "rendering Pause State" << std::endl;
	//first we render the game state 
	StateManager::GetStates().front()->Render();
	//now we render the rest of pause state 
	SDL_SetRenderDrawBlendMode(Game::GetInstance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 128, 128, 128, 128);
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(Game::GetInstance().GetRenderer(), &rect);

	if (Game::GetInstance().KeyDown(SDL_SCANCODE_R))
	{
		StateManager::PushState(new GameState());
	}
}

void PauseState::Exit()
{
	std::cout << "exiting pause state" << std::endl;
}