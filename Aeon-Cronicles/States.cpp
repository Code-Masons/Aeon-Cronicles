#include <iostream>
#include "States.h"
#include "StateManager.h"
#include "CollisionManager.h"
#include "MathManager.h"
#include "EventManager.h"


void TitleState::Enter()
{
	std::cout << "entering title state " << std::endl;

	GameName = new GameObject(Game::kWidth / 2 - 300, Game::kHeight / 3 - 200, 600, 400, 100, 100, 100, 255);
	StartGameButton = new UIButton(Game::kWidth / 2 - 100, Game::kHeight * 3 / 4 - 100, 200, 200);

	TitleStateTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/titleState.png");
	StartGameButtonTexture= IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/start.png");
}
void TitleState::Update(float deltaTime)
{
	//if (Game::GetInstance().KeyDown(SDL_SCANCODE_G))//press g to go to game state
	//{
	//	std::cout << "changing to game state" << std::endl;
	//	StateManager::ChangeState(new GameState());//change to new game state
	//}

	if (EventManager::MousePressed(1))
	{
		StartGameButton->HandleEvent();
		if (StartGameButton->CheckIsHovered())
		{
			std::cout << "changing to game state" << std::endl;
			StateManager::ChangeState(new GameState());//change to new game state
		}
	}
}
void TitleState::Render()
{
	std::cout << "rendering title state" << std::endl;

	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 48, 25, 52, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());

	SDL_RenderCopy(pRenderer, TitleStateTexture, nullptr, nullptr);

	SDL_Rect TitleButtonRect = MathManager::ConvertFRect2Rect(StartGameButton->GetTransform());
	SDL_RenderCopy(pRenderer, StartGameButtonTexture, nullptr, &TitleButtonRect);
}
void TitleState::Exit()
{
	std::cout << "exiting title state" << std::endl;
}


void GameState::Enter()
{

	std::cout << "entering game state" << std::endl;
	
	//define game objects here
	m_player = new GameObject(Game::kWidth / 2, Game::kHeight / 2, 100, 100, 0, 200, 0, 255);
	m_enemy = new GameObject(100, 100, 100, 100, 0, 200, 0, 255);
  
	//tileLevel = new TileLevel();
	m_background = new GameObject(0, 0, 2000, Game::kHeight);
	tileLevel = new TileLevel(Game::kWidth, Game::kHeight);
	tileLevel->loadLevelData();

	//load textures for game state here
	m_pPlayerTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/playerbullet.png");
	m_pEnemyTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/enemybullet.png");
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/background.png");
}
void GameState::Update(float deltaTime)
{
	int levelWidth, levelHeight;
	SDL_QueryTexture(m_pBackgroundTexture, NULL, NULL, &levelWidth, &levelHeight);
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_P))
	{
		std::cout << "changing to pause state" << std::endl;
		StateManager::PushState(new PauseState());
	}

	else
	{
		//ENEMY UPDATE
		if (m_player->UpdatePositionX(0) > m_enemy->UpdatePositionX(0))
		{
			m_enemy->UpdatePositionX(kEnemySpeed * deltaTime);
		}
		else
		{
			m_enemy->UpdatePositionX(-kEnemySpeed * deltaTime);
		}
		if (m_player->UpdatePositionY(0) > m_enemy->UpdatePositionY(0))
		{
			m_enemy->UpdatePositionY(kEnemySpeed * deltaTime);
		}
		else
		{
			m_enemy->UpdatePositionY(-kEnemySpeed * deltaTime);
		}

		//PLAYER UPDATE
		if (Game::GetInstance().KeyDown(SDL_SCANCODE_A) && m_player->UpdatePositionX(0) > 0)
		{
			m_player->UpdatePositionX(-kPlayerSpeed * deltaTime);
		}

		if (Game::GetInstance().KeyDown(SDL_SCANCODE_D) && m_player->UpdatePositionX(0) <= Game::kWidth - m_player->GetObjectWidth())
		{
			m_player->UpdatePositionX(kPlayerSpeed * deltaTime);
		}

		if (Game::GetInstance().KeyDown(SDL_SCANCODE_SPACE))
		{
			m_player->UpdatePositionY(kPlayerJumpForce * deltaTime);
		}

		if (CollisionManager::AABBCheck(m_player->GetTransform(), m_enemy->GetTransform()))
		{
			std::cout << "player collides with enemy" << std::endl;
			StateManager::PushState(new LoseState);
		}

		if (Game::GetInstance().KeyDown(SDL_SCANCODE_W))
		{
			std::cout << "changing to win state" << std::endl;
			StateManager::PushState(new WinState());
		}
	}
	float gravity;
	if(m_player->UpdatePositionY(0)>Game::kHeight-m_player->GetObjectHeight())
	{
		gravity = 0;
	}
	else
	{
		gravity = 0.5;
	}
	m_player->UpdatePositionY(gravity);
	camera.x = m_player->GetTransform().x - Game::kWidth / 2;
	camera.y = m_player->GetTransform().y - Game::kHeight / 2;

	//keep camera in bounds
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > lWidth - camera.w)
		camera.x = lWidth - camera.w;
	if (camera.y > lHeight - camera.h)
		camera.y = lHeight - camera.h;

	if (camera.x + camera.w >= levelWidth)
		camera.x = levelWidth - 2500;
	if (camera.y + camera.h >= levelHeight)
		camera.y = levelHeight - Game::kHeight;
}
void GameState::Render()
{
	std::cout << "rendering game state..." << std::endl;

	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();

	SDL_SetRenderDrawColor(pRenderer, 0, 0, 200, 255);
	SDL_RenderClear(pRenderer);

	SDL_Rect backgroundIntRect = MathManager::ConvertFRect2Rect(m_background->GetTransform());
	SDL_RenderCopy(pRenderer, m_pBackgroundTexture, &camera, &backgroundIntRect);
	
	SDL_Rect playerIntRect = MathManager::ConvertFRect2Rect(m_player->GetTransform());
	SDL_RenderCopy(pRenderer, m_pPlayerTexture, nullptr, &playerIntRect);

	SDL_Rect enemyintRect = MathManager::ConvertFRect2Rect(m_enemy->GetTransform());
	SDL_RenderCopy(pRenderer, m_pEnemyTexture, nullptr, &enemyintRect);

	tileLevel->loadLevelTextures(pRenderer);
	tileLevel->render(pRenderer);
  
	playerIntRect.x = m_player->GetTransform().x - camera.x;
	playerIntRect.y = m_player->GetTransform().y - camera.y;
}
void GameState::Resume()
{
	std::cout << "resuming game state" << std::endl;
}
void GameState::Exit()
{
	std::cout << "exiting game state" << std::endl;

	delete m_player;
	m_player = nullptr;

	delete m_enemy;
	m_enemy = nullptr;

	delete tileLevel;
	tileLevel = nullptr;
  
	delete m_background;
	m_background = nullptr;

	SDL_DestroyTexture(m_pPlayerTexture);
	m_pPlayerTexture = nullptr;

	SDL_DestroyTexture(m_pEnemyTexture);

	m_pEnemyTexture = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);


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


void WinState::Enter()
{
	std::cout << "entering win state" << std::endl;

	WinStateTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/Win.png");
	//RetryButton = new UIButton(Game::kWidth / 2 - 100, Game::kHeight / 2 - 200, 200, 200);
	//RetryButtonTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/playerbullet.png");
	MainMenuButton = new UIButton(Game::kWidth / 2 - 100, Game::kHeight / 2 + 100, 200, 200);
	MainMenuButtonTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/mainmenu.png");
}	 
void WinState::Update(float deltaTime)
{
	//if (Game::GetInstance().KeyDown(SDL_SCANCODE_R))
	//{
	//	std::cout << "changing to title state" << std::endl;
	//	StateManager::ChangeState(new TitleState());
	//}

	//if (EventManager::MousePressed(1))
	//{
	//	RetryButton->HandleEvent();
	//	if (RetryButton->CheckIsHovered())
	//	{
	//		std::cout << "changing to game state" << std::endl;
	//		StateManager::ChangeState(new GameState());//change to new game state
	//	}
	//}
	if (EventManager::MousePressed(1))
	{
		MainMenuButton->HandleEvent();
		if (MainMenuButton->CheckIsHovered())
		{
			std::cout << "changing to title state" << std::endl;
			StateManager::ChangeState(new TitleState());//change to new title state
		}
	}
}
void WinState::Render()
{
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();


	SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
	SDL_RenderClear(pRenderer);

	SDL_RenderCopy(pRenderer, WinStateTexture, nullptr, nullptr);
	//SDL_Rect RetryButtonRect = MathManager::ConvertFRect2Rect(RetryButton->GetTransform());
	//SDL_RenderCopy(pRenderer, RetryButtonTexture, nullptr, &RetryButtonRect);
	SDL_Rect MainMenuButtonRect = MathManager::ConvertFRect2Rect(MainMenuButton->GetTransform());
	SDL_RenderCopy(pRenderer, MainMenuButtonTexture, nullptr, &MainMenuButtonRect);
}
void WinState::Exit()
{
	std::cout << "exiting lose state" << std::endl;
}


void LoseState::Enter()
{
	std::cout << "entering lose state" << std::endl;

	LoseStateTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/Lose.png");
	//RetryButton = new UIButton(Game::kWidth / 2 - 100, Game::kHeight / 2 - 200, 200, 200);
	//RetryButtonTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/playerbullet.png");
	MainMenuButton = new UIButton(Game::kWidth / 2 - 100, Game::kHeight / 2 + 100, 200, 200);
	MainMenuButtonTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/mainmenu.png");
}
void LoseState::Update(float deltaTime)
{
	//if (Game::GetInstance().KeyDown(SDL_SCANCODE_R))
	//{
	//	std::cout << "changing to title state" << std::endl;
	//	StateManager::ChangeState(new TitleState());
	//}
	//if (EventManager::MousePressed(1))
	//{
	//	RetryButton->HandleEvent();
	//	if (RetryButton->CheckIsHovered())
	//	{
	//		std::cout << "changing to game state" << std::endl;
	//		StateManager::ChangeState(new GameState());//change to new game state
	//	}
	//}
	if (EventManager::MousePressed(1))
	{
		MainMenuButton->HandleEvent();
		if (MainMenuButton->CheckIsHovered())
		{
			std::cout << "changing to title state" << std::endl;
			StateManager::ChangeState(new TitleState());//change to new title state
		}
	}
}
void LoseState::Render()
{
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();


	SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
	SDL_RenderClear(pRenderer);

	SDL_RenderCopy(pRenderer, LoseStateTexture, nullptr, nullptr);
	//SDL_Rect RetryButtonRect = MathManager::ConvertFRect2Rect(RetryButton->GetTransform());
	//SDL_RenderCopy(pRenderer, RetryButtonTexture, nullptr, &RetryButtonRect);
	SDL_Rect MainMenuButtonRect = MathManager::ConvertFRect2Rect(MainMenuButton->GetTransform());
	SDL_RenderCopy(pRenderer, MainMenuButtonTexture, nullptr, &MainMenuButtonRect);
}
void LoseState::Exit()
{
	std::cout << "exiting lose state" << std::endl;
}