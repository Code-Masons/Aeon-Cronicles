#include <iostream>
#include "States.h"
#include "StateManager.h"
#include "Game.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "MathManager.h"


void TitleState::Enter()
{
	std::cout << "entering title state " << std::endl;

	GameName = new GameObject(Game::kWidth / 2 - 300, Game::kHeight / 3 - 200, 600, 400, 100, 100, 100, 255);

	TitleStateTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/titleState.png");
}
void TitleState::Update(float deltaTime)
{

	if (Game::GetInstance().KeyDown(SDL_SCANCODE_G))//press g to go to game state
	{
		std::cout << "changing to game state" << std::endl;
		StateManager::ChangeState(new OfficeState());//change to new game state
	}
}
void TitleState::Render()
{
	std::cout << "rendering title state" << std::endl;

	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 48, 25, 52, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());

	SDL_RenderCopy(pRenderer, TitleStateTexture, nullptr, nullptr);
}
void TitleState::Exit()
{
	std::cout << "exiting title state" << std::endl;
}


void OfficeState::Enter()
{

	std::cout << "entering game state" << std::endl;

	m_background = new GameObject(0, 0, 2000, Game::kHeight);

	//load textures for game state here
	m_pPlayerTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/office/playerPrologue.png");
	m_pTrophyTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/office/prideItem.png");
	m_pWomanWorkerTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/office/womanWorker.png");
	m_pMaleWorkerTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/office/maleOfficeWorker.png");
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/office/officebackground.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/office/officeText.png");
	m_pContinueTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/office/pressC.png");
}	
void OfficeState::Update(float deltaTime)
{
	int levelWidth, levelHeight;
	SDL_QueryTexture(m_pBackgroundTexture, NULL, NULL, &levelWidth, &levelHeight);
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_P))
	{
		std::cout << "changing to pause state" << std::endl;
		StateManager::PushState(new PauseState());
	}

	if (Game::GetInstance().KeyReleased(SDL_SCANCODE_C))//press C to go to game state
	{
		std::cout << "changing to street state" << std::endl;
		StateManager::ChangeState(new StreetState());//change to new game state
	}

}
void OfficeState::Render()
{
	std::cout << "rendering office state..." << std::endl;

	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();

	SDL_SetRenderDrawColor(pRenderer, 0, 0, 200, 255);
	SDL_RenderClear(pRenderer);

	SDL_Rect backgroundIntRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(pRenderer, m_pBackgroundTexture, NULL, &backgroundIntRect);
	
	SDL_Rect playerIntRect = {50,400,250,250};
	SDL_RenderCopy(pRenderer, m_pPlayerTexture, nullptr, &playerIntRect);

	SDL_Rect trophyRect = { 235,480,50,50 };
	SDL_RenderCopy(pRenderer, m_pTrophyTexture, nullptr, &trophyRect);

	SDL_Rect womanWorkerRect = {300,400,250,250};
	SDL_RenderCopy(pRenderer, m_pWomanWorkerTexture, nullptr, &womanWorkerRect);

	SDL_Rect maleWorkerRect = { 550,400,250,250 };
	SDL_RenderCopy(pRenderer, m_pMaleWorkerTexture, nullptr, &maleWorkerRect);

	SDL_Rect officeTextRect = { 250,20,500,350 };
	SDL_RenderCopy(pRenderer, m_pTextTexture, nullptr, &officeTextRect);

	SDL_Rect continueRect = { 700,700,500,350 };
	SDL_RenderCopy(pRenderer, m_pContinueTexture, nullptr, &continueRect);
 
}
void OfficeState::Resume()
{
	std::cout << "resuming office state" << std::endl;
}
void OfficeState::Exit()
{
	std::cout << "exiting office state" << std::endl;

	delete m_player;
	m_player = nullptr;

	delete m_trophy;
	m_trophy = nullptr;

	delete m_maleWorker;
	m_maleWorker = nullptr;

	delete m_womanWorker;
	m_womanWorker = nullptr;

	delete m_text;
	m_text = nullptr;

	delete m_continue;
	m_continue = nullptr;

  
	delete m_background;
	m_background = nullptr;

	SDL_DestroyTexture(m_pPlayerTexture);
	m_pPlayerTexture = nullptr;

	SDL_DestroyTexture(m_pTrophyTexture);
	m_pTrophyTexture = nullptr;

	SDL_DestroyTexture(m_pMaleWorkerTexture);
	m_pMaleWorkerTexture = nullptr;

	SDL_DestroyTexture(m_pWomanWorkerTexture);
	m_pWomanWorkerTexture = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pContinueTexture);
	m_pContinueTexture = nullptr;

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
		StateManager::PushState(new OfficeState());
	}
}
void PauseState::Exit()
{
	std::cout << "exiting pause state" << std::endl;
}

void StreetState::Enter()
{
	std::cout << "entering street state.. " << std::endl;

	m_pBackground = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/street/streetBackground.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/street/streetText.png");
	m_pContinueTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/street/pressCWhite.png");
}

void StreetState::Update(float deltaTime)
{
	

	if (Game::GetInstance().KeyReleased (SDL_SCANCODE_C))//press C to go to game state
	{
		std::cout << "changing to car state" << std::endl;
		StateManager::ChangeState(new CarState());//change to new game state
	}

}

void StreetState::Render()
{
	std::cout << "rendering street state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0, Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackground, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,150, 600,450 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect continueRect = { 700,700, 600,450 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pContinueTexture, NULL, &continueRect);
}

void StreetState::Exit()
{
	std::cout << "exiting street state.." << std::endl;

	delete m_background;
	m_background = nullptr;

	delete m_text;
	m_text = nullptr;

	SDL_DestroyTexture(m_pBackground);
	m_pBackground = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

}

void CarState::Enter()
{
	std::cout << "entering car state.." << std::endl;
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/carDash/background.png");
	
}

void CarState::Update(float deltaTime)
{

}

void CarState::Render()
{
	std::cout << "rendering car state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

}

void CarState::Exit()
{
	std::cout << "exiting car state.." << std::endl;
}

void WinState::Enter()
{
	std::cout << "entering win state" << std::endl;
}	 
void WinState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_R))
	{
		std::cout << "changing to title state" << std::endl;
		StateManager::ChangeState(new TitleState());
	}
}
void WinState::Render()
{
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();


	SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
	SDL_RenderClear(pRenderer);
}
void WinState::Exit()
{
	std::cout << "exiting lose state" << std::endl;
}


void LoseState::Enter()
{
	std::cout << "entering lose state" << std::endl;
}
void LoseState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_R))
	{
		std::cout << "changing to title state" << std::endl;
		StateManager::ChangeState(new TitleState());
	}
}
void LoseState::Render()
{
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();


	SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
	SDL_RenderClear(pRenderer);
}
void LoseState::Exit()
{
	std::cout << "exiting lose state" << std::endl;
}