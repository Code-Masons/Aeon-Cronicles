#include <iostream>
#include "States.h"
#include "StateManager.h"
#include "Game.h"
#include "GameObject.h"
#include "EventManager.h"
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

	if (Game::GetInstance().KeyDown(SDL_SCANCODE_G))//press g to go to office state
	{
		std::cout << "changing to game state" << std::endl;
		StateManager::ChangeState(new OfficeState());//change to new office state
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

	if (Game::GetInstance().KeyDown(SDL_SCANCODE_C))//press C to go to game state
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

	if (EventManager::KeyPressed(SDL_SCANCODE_R))
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
	m_pContinueTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/street/pressX.png");


}

void StreetState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_X))//press X to go to game state
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
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/carDash/wrathText.png");
	m_pContinueTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/carDash/pressC.png");

}

void CarState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_C))//press c to go to game state
	{
		std::cout << "changing to truck state" << std::endl;
		StateManager::ChangeState(new TruckState());//change to new truck state
	}
}

void CarState::Render()
{
	std::cout << "rendering car state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 300,50,400,350 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect cRect = { 750,700,200,350 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pContinueTexture, NULL, &cRect);

}

void CarState::Exit()
{
	std::cout << "exiting car state.." << std::endl;

	delete m_background;
	m_background = nullptr;

	delete m_text;
	m_text = nullptr;

	delete m_continue;
	m_continue = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pContinueTexture);
	m_pContinueTexture = nullptr;


}

void TruckState::Enter()
{
	std::cout << "entering truck state.." << std::endl;

	m_pTruckTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/truck/truck.png");
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/truck/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/truck/truckText.png");
	m_pPressXTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/truck/pressX.png");
}

void TruckState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_X))//press X to go to hell start state state
	{
		std::cout << "changing to hell state" << std::endl;
		StateManager::ChangeState(new HellState());//change to new hell start state
	}
}

void TruckState::Render()
{

	std::cout << "rendering truck state.." << std::endl;

	SDL_Rect truckRect = { 0,10,1200,750 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTruckTexture, NULL, &truckRect);

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 200,500,700,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect xRect = { 750,20,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pPressXTexture, NULL, &xRect);

}

void TruckState::Exit()
{
	std::cout << "exiting truck state.." << std::endl;

	delete m_background;
	m_background = nullptr;

	delete m_text;
	m_text = nullptr;

	delete m_pressX;
	m_pressX = nullptr;

	delete m_truck;
	m_truck = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pPressXTexture);
	m_pPressXTexture = nullptr;

	SDL_DestroyTexture(m_pTruckTexture);
	m_pTruckTexture = nullptr;
}

//////////////////CHAPTER 1 STATES START////////////////////////////

void HellState::Enter()
{
	std::cout << "entering hell state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/enterHell/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/enterHell/text.png");
	m_pPressCTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/enterHell/pressC.png");
}

void HellState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_C))//press X to go to hell start state state
	{
		std::cout << "changing to casino state" << std::endl;
		StateManager::ChangeState(new CasinoState());//change to new hell start state
	}
}

void HellState::Render()
{
	std::cout << "rendering Hell state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 200,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect cRect = { 750,700,200,350 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pPressCTexture, NULL, &cRect);
}

void HellState::Exit()
{
	std::cout << "exiting hell state.." << std::endl;

	delete m_background;
	m_background = nullptr;

	delete m_Text;
	m_Text = nullptr;

	delete m_PressC;
	m_PressC = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pPressCTexture);
	m_pPressCTexture = nullptr;
}

void CasinoState::Enter()
{
	std::cout << "entering casino state.. " << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casino/background.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casino/devil.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casino/text.png");
	m_pPressXTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casino/pressX.png");
}

void CasinoState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_X))//press X to go to casino choice state
	{
		std::cout << "changing to casino choice state" << std::endl;
		StateManager::ChangeState(new CasinoChoiceState());//change to new casino choice start state
	}
}

void CasinoState::Render()
{
	std::cout << " rendering casino state.. " << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect devilRect = { 300,275,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pDevilTexture, NULL, &devilRect);

	SDL_Rect textRect = { 300,10,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect xRect = { 750,700,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pPressXTexture, NULL, &xRect);
}

void CasinoState::Exit()
{
	std::cout << " exiting casino state.. " << std::endl;

	delete m_background;
	m_background = nullptr;

	delete m_text;
	m_text = nullptr;

	delete m_devil;
	m_devil = nullptr;

	delete m_pressX;
	m_pressX = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;

	SDL_DestroyTexture(m_pPressXTexture);
	m_pPressXTexture = nullptr;
}

void CasinoChoiceState::Enter()
{
	std::cout << "entering casino choice state.. " << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casino/background.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casino/devil.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoChoice/text.png");
	m_pPress1Texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoChoice/wrongText.png");
	m_pPress2Texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoChoice/rightText.png");
}

void CasinoChoiceState::Update(float deltaTime)
{

	if (Game::GetInstance().KeyDown(SDL_SCANCODE_1))//press 1 to go to casino lose state
	{
		std::cout << "changing to casino choice state" << std::endl;
		StateManager::ChangeState(new CasinoLoseState());//change to new casino lose start state
	}

	else if (Game::GetInstance().KeyDown(SDL_SCANCODE_2))//press 2 to go to casino exit state
	{
		std::cout << "changing to casino choice state" << std::endl;
		StateManager::ChangeState(new CasinoExitState());//change to new casino exit start state
	}
}

void CasinoChoiceState::Render()
{
	std::cout << "rendering casino choice state.. " << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect devilRect = { 300,275,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pDevilTexture, NULL, &devilRect);

	SDL_Rect textRect = { 300,10,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect TextRect = { 210,700,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pPress1Texture, NULL, &TextRect);

	SDL_Rect Text2Rect = { 750,700,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pPress2Texture, NULL, &Text2Rect);
}

void CasinoChoiceState::Exit()
{
	std::cout << "exiting casino choice state.. " << std::endl;

	delete m_background;
	m_background = nullptr;

	delete m_text;
	m_text = nullptr;

	delete m_devil;
	m_devil = nullptr;

	delete m_press1;
	m_press1 = nullptr;

	delete m_press2;
	m_press2 = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;

	SDL_DestroyTexture(m_pPress1Texture);
	m_pPress1Texture = nullptr;

	SDL_DestroyTexture(m_pPress2Texture);
	m_pPress2Texture = nullptr;
}

void CasinoExitState::Enter()
{
	std::cout << "entering casino exit state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoExit/background.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casino/devil.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoExit/text.png");
}

void CasinoExitState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_C))//press C to go to pride enter state
	{
		std::cout << "changing to casino choice state" << std::endl;
		StateManager::ChangeState(new PrideEnterState());//change to new casino pride enter state
	}

}

void CasinoExitState::Render()
{
	std::cout << "rendering casino exit state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect devilRect = { 300,275,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pDevilTexture, NULL, &devilRect);

	SDL_Rect textRect = { 300,10,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);
}

void CasinoExitState::Exit()
{
	std::cout << "exiting casino exit state.." << std::endl;

	delete m_background;
	m_background = nullptr;

	delete m_text;
	m_text = nullptr;

	delete m_devil;
	m_devil = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;
}

void CasinoLoseState::Enter()
{
	std::cout << "entering casino lose state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoExit/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoLose/text.png");
	m_pPlayerTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoLose/player.png");
}

void CasinoLoseState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_R))//press R to go to title state
	{
		std::cout << "changing to casino choice state" << std::endl;
		StateManager::ChangeState(new TitleState());//change to new title state
	}
}

void CasinoLoseState::Render()
{
	std::cout << "rendering casino lose state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 300,10,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect playerRect = { 270,300,300,300 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pPlayerTexture, NULL, &playerRect);
}

void CasinoLoseState::Exit()
{
	std::cout << "exiting casino lose state.." << std::endl;
	delete m_background;
	m_background = nullptr;

	delete m_text;
	m_text = nullptr;

	delete m_player;
	m_player = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pPlayerTexture);
	m_pPlayerTexture = nullptr;

}

////////////////////CHAPTER 2 START//////////////////////////////////
void PrideEnterState::Enter()
{
	std::cout << "entering pride enter state.." << std::endl;
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideEnter/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideEnter/text.png");
}

void PrideEnterState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_X))//press X to go to pride choice state
	{
		std::cout << "changing to pride choice state" << std::endl;
		StateManager::ChangeState(new PrideChoiceState());//change to new pride choice state
	}
}

void PrideEnterState::Render()
{
	std::cout << "rendering pride enter state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,575,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);
}

void PrideEnterState::Exit()
{
	std::cout << "exiting pride enter state.." << std::endl;

	delete m_background;
	m_background = nullptr;

	delete m_text;
	m_text = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;
}

void PrideChoiceState::Enter()
{
	std::cout << "entering pride choice state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideEnter/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideChoice/text.png");
}

void PrideChoiceState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_1))//press 1 to go to pride exit state
	{
		std::cout << "changing to pride choice state" << std::endl;
		StateManager::ChangeState(new PrideExitState());//change to new pride exit state
	}

	else if (Game::GetInstance().KeyDown(SDL_SCANCODE_2))//press 2 to go to pride lose state
	{
		std::cout << "changing to pride choice state" << std::endl;
		StateManager::ChangeState(new PrideLoseState());//change to new pride lose state
	}
}

void PrideChoiceState::Render()
{
	std::cout << "rendering pride choice state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,575,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);
}

void PrideChoiceState::Exit()
{
	std::cout << "exiting pride choice state.." << std::endl;

	delete m_background;
	m_background = nullptr;

	delete m_text;
	m_text = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;
}

void PrideExitState::Enter()
{
	std::cout << "entering pride exit state.." << std::endl;
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideExit/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideExit/text.png");
}

void PrideExitState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_C))//press C to go to lust enter state
	{
		std::cout << "changing to casino choice state" << std::endl;
		StateManager::ChangeState(new LustEnterState());//change to new lust enter state
	}
}

void PrideExitState::Render()
{
	std::cout << "rendering pride exit state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,575,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);
}

void PrideExitState::Exit()
{
	std::cout << "exiting pride exit state.." << std::endl;

	delete m_background;
	m_background = nullptr;

	delete m_text;
	m_text = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;
}

void PrideLoseState::Enter()
{
	std::cout << "enter pride lose state.." << std::endl;
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideLose/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideLose/text.png");
	m_pPlayerTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideLose/player.png");
}

void PrideLoseState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_R))//press R to go to title state
	{
		std::cout << "changing to casino choice state" << std::endl;
		StateManager::ChangeState(new TitleState());//change to new title state
	}
}

void PrideLoseState::Render()
{
	std::cout << "rendering pride lose state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,575,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect playerRect = { 370,45,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pPlayerTexture, NULL, &playerRect);
}

void PrideLoseState::Exit()
{
	std::cout << "exiting pride lose state.." << std::endl;

	delete m_background;
	m_background = nullptr;

	delete m_text;
	m_text = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;
}

////////////////////CHAPTER 3 START//////////////////////////////////
void LustEnterState::Enter()
{
	std::cout << "entering lust enter state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/LustEnter/text.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/devil.png");
}

void LustEnterState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_X))
	{
		std::cout << "changing to lust choice state" << std::endl;
		StateManager::ChangeState(new LustChoiceState());
	}
}

void LustEnterState::Render()
{
	std::cout << "rendering lust enter state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect devilRect = { 700,475,200,200 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pDevilTexture, NULL, &devilRect);
}

void LustEnterState::Exit()
{
	std::cout << "exiting lust enter state.." << std::endl;

	delete m_background;
	m_background = nullptr;

	delete m_text;
	m_text = nullptr;

	delete m_devil;
	m_devil = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;
}

void LustChoiceState::Enter()
{
	std::cout << "entering lust choice state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/LustChoice/text.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/devil.png");
}

void LustChoiceState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_1))//press 1 to go to lust exit state
	{
		std::cout << "changing to pride choice state" << std::endl;
		StateManager::ChangeState(new LustExitState());//change to new lust exit state
	}

	if (Game::GetInstance().KeyDown(SDL_SCANCODE_2))//press 2 to go to lust lose state
	{
		std::cout << "changing to pride choice state" << std::endl;
		StateManager::ChangeState(new LustLoseState());//change to new lust lose state
	}
}

void LustChoiceState::Render()
{
	std::cout << "rendering lust choice state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect devilRect = { 700,475,200,200 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pDevilTexture, NULL, &devilRect);
}

void LustChoiceState::Exit()
{
	std::cout << "exiting lust choice state" << std::endl;

	delete m_background;
	m_background = nullptr;

	delete m_text;
	m_text = nullptr;

	delete m_devil;
	m_devil = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;
}
////////////////////CHAPTER 3 START//////////////////////////////////
void LustExitState::Enter()
{
	std::cout << "entering lust exit state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/lustExit/text.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/devil.png");
}

void LustExitState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_X))
	{
		std::cout << "changing to casino choice state" << std::endl;
		StateManager::ChangeState(new EnvyEnterState());
	}
}

void LustExitState::Render()
{
	std::cout << "rendering lust exit state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect devilRect = { 700,475,200,200 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pDevilTexture, NULL, &devilRect);
}

void LustExitState::Exit()
{
	std::cout << "exiting lust exit state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;
}

void LustLoseState::Enter()
{
	std::cout << "entering lust lose state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/lustLose/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/lustLose/text.png");
}

void LustLoseState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_R))//press R to go to title state
	{
		std::cout << "changing to casino choice state" << std::endl;
		StateManager::ChangeState(new TitleState());//change to new title state
	}
}

void LustLoseState::Render()
{
	std::cout << "rendering lust lose state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);
}

void LustLoseState::Exit()
{
	std::cout << "exiting lust lose state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;
}
////////////////////CHAPTER 4 START//////////////////////////////////

void EnvyEnterState::Enter()
{
	std::cout << "entering envy enter state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/envyEnter/text.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/devil.png");
}

void EnvyEnterState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_X))
	{
		std::cout << "changing to envy choice state" << std::endl;
		StateManager::ChangeState(new EnvyChoiceState());
	}
}

void EnvyEnterState::Render()
{
	std::cout << "rendering envy enter state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect devilRect = { 350,270,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pDevilTexture, NULL, &devilRect);
}

void EnvyEnterState::Exit()
{
	std::cout << "exiting envy enter state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;
}

void EnvyChoiceState::Enter()
{
	std::cout << "entering envy choice state.. " << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/envyChoice/text.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/devil.png");
}

void EnvyChoiceState::Update(float deltaTime)
{

	if (Game::GetInstance().KeyDown(SDL_SCANCODE_1))
	{
		std::cout << "changing to envy lose state" << std::endl;
		StateManager::ChangeState(new EnvyLoseState());
	}

	else if (Game::GetInstance().KeyDown(SDL_SCANCODE_2))
	{
		std::cout << "changing to envy exit state" << std::endl;
		StateManager::ChangeState(new EnvyExitState());
	}
}

void EnvyChoiceState::Render()
{
	std::cout << "rendering envy choice state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect devilRect = { 350,270,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pDevilTexture, NULL, &devilRect);
}

void EnvyChoiceState::Exit()
{
	std::cout << "exiting envy choice state" << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;
}

void EnvyExitState::Enter()
{
	std::cout << "entering envy exit state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/envyExit/text.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/devil.png");
}

void EnvyExitState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_C))
	{
		std::cout << "changing to wrath enter state" << std::endl;
		StateManager::ChangeState(new WrathEnterState());
	}
}

void EnvyExitState::Render()
{
	std::cout << "rendering envy exit state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect devilRect = { 350,270,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pDevilTexture, NULL, &devilRect);
}

void EnvyExitState::Exit()
{
	std::cout << "exiting envy exit state" << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;
}

void EnvyLoseState::Enter()
{
	std::cout << "entering envy lose state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/envyLose/text.png");
}

void EnvyLoseState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_R))//press R to go to title state
	{
		std::cout << "changing to casino choice state" << std::endl;
		StateManager::ChangeState(new TitleState());//change to new title state
	}
}

void EnvyLoseState::Render()
{
	std::cout << "rendering envy lose state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,300,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

}

void EnvyLoseState::Exit()
{
	std::cout << "exiting envy lose state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

}
////////////////////CHAPTER 5 START//////////////////////////////////
void WrathEnterState::Enter()
{
	std::cout << "entering wrath enter state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter5/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter5/wrathEnter/text.png");
}

void WrathEnterState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_C))
	{
		std::cout << "changing to wrath choice state" << std::endl;
		StateManager::ChangeState(new WrathChoiceState());
	}
}

void WrathEnterState::Render()
{
	std::cout << "rendering wrath enter state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);
}

void WrathEnterState::Exit()
{
	std::cout << "exiting wrath enter state" << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;
}

void WrathChoiceState::Enter()
{
	std::cout << "entering wrath choice state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter5/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter5/wrathChoice/text.png");
}

void WrathChoiceState::Update(float deltaTime)
{

}

void WrathChoiceState::Render()
{
	std::cout << "rendering wrath choice state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);
}

void WrathChoiceState::Exit()
{
	std::cout << "exiting wrath choice state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;
}

////////////////////CHAPTER 7 START//////////////////////////////////
void SlothEnterState::Enter()
{
	std::cout << "entering first sloth state.." << std::endl;
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/enterSloth/background.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/enterSloth/devil.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/enterSloth/text.png");
}

void SlothEnterState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_X))//press X to go to sloth choice state
	{
		std::cout << "changing to casino choice state" << std::endl;
		StateManager::ChangeState(new SlothChoiceState());//change to new sloth choice start state
	}
}

void SlothEnterState::Render()
{
	std::cout << "rendering first sloth state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect devilRect = { 300,200,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pDevilTexture, NULL, &devilRect);

	SDL_Rect textRect = { 500,20,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);
}

void SlothEnterState::Exit()
{
	std::cout << "exiting first sloth state.." << std::endl;

	delete m_background;
	m_background = nullptr;

	delete m_text;
	m_text = nullptr;

	delete m_devil;
	m_devil = nullptr;
}

void SlothChoiceState::Enter()
{
	std::cout << "entering second sloth state.." << std::endl;
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/enterSloth/background.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/enterSloth/devil.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/slothChoice/text.png");
}

void SlothChoiceState::Update(float deltaTime)
{

}

void SlothChoiceState::Render()
{
	std::cout << "rendering second sloth state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect devilRect = { 300,200,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pDevilTexture, NULL, &devilRect);

	SDL_Rect textRect = { 500,20,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);
}

void SlothChoiceState::Exit()
{
	std::cout << "exiting second sloth state.." << std::endl;

	delete m_background;
	m_background = nullptr;

	delete m_text;
	m_text = nullptr;

	delete m_devil;
	m_devil = nullptr;
}

void SlothExitState::Enter()
{
	std::cout << "entering sloth exit state.." << std::endl;
}

void SlothExitState::Update(float deltaTime)
{

}

void SlothExitState::Render()
{
	std::cout << "rendering sloth exit state.." << std::endl;
}

void SlothExitState::Exit()
{
	std::cout << "exiting sloth exit state.." << std::endl;
}

void WinState::Enter()
{
	std::cout << "entering win state.." << std::endl;
}	 
void WinState::Update(float deltaTime)
{
	if (EventManager::KeyPressed(SDL_SCANCODE_R))
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
	std::cout << "exiting lose state.." << std::endl;
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