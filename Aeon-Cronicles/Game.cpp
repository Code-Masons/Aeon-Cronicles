#include "Game.h"
#include "StateManager.h"
#include "States.h"
#include "EventManager.h"
#include <iostream>

Game::Game()
	: m_running(false)
	, m_pWindow(nullptr)
	, m_pRenderer(nullptr)
	, m_RectangleTransform { kWidth / 2, kHeight / 2, 100, 100 }
	, m_keyStates(nullptr)
{

}

int Game::Init(const char* title, int xpos, int ypos)
{
	std::cout << "initalizing engine... " << std::endl;

	int errorCode = SDL_Init(SDL_INIT_EVERYTHING);//initializing SDL
	if (errorCode == 0)
	{
		std::cout << "SDL_Init succeded" << std::endl;
	}

	else//if there is an error console will say init failed and will display error code 
	{
		std::cout << "SDL_Init failed " << errorCode << std::endl;
		system("puase");
		return errorCode;
	}
	//create window at center of the screen with dimentions 1024, 769
	m_pWindow = SDL_CreateWindow("Aeon Cronicles", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kWidth, kHeight, 0);

	if (m_pWindow != nullptr)//if pWindow is not equal to null then the window has successfully been created
	{
		std::cout << "SDL_CreateWindow succeeded" << std::endl;
	}
	else
	{
		std::cout << "SDL_CreatWindow() failed error:" << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		system("pause");
		return -1;
	}

	//creating renderer 
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

	if (m_pRenderer != nullptr)
	{
		std::cout << "SDL_CreateRenderer succeeded" << std::endl;
	}
	else
	{
		std::cout << "SDL_CreateRenderer() failed error:" << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		system("pause");
		return -1;
	}

	EventManager::Init();

	std::cout << "initialization successful" << std::endl;

	StateManager::PushState(new TitleState());

	m_keyStates = SDL_GetKeyboardState(nullptr);

	m_running = true;
	return 0;
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::HandleEvents()
{

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_running = false;
			break;
		}

	}
}

void Game::Quit()
{
	m_running = false;
}

void Game::Update(float deltaTime)
{
	StateManager::Update(deltaTime);
}

void Game::Render()
{
	StateManager::Render();
	SDL_RenderPresent(m_pRenderer);
}

bool Game::KeyDown(SDL_Scancode key)
{
	if (m_keyStates)
	{
		return m_keyStates[key] == 1;
	}
	return false;
}

void Game::Clean()
{
	std::cout << "cleaning engine" << std::endl;
	StateManager::Quit();
	//EventManager::Quit();
	//TextureManager::Quit();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();

	delete this;
}

Game& Game::GetInstance()
{
	static Game* instance = new Game();
	return *instance;
}
