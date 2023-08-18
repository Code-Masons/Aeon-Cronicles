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
	start = new UIButton(Game::kWidth / 2 - 100, Game::kHeight * 3 / 4 - 100, 200, 200);

	m_pStartTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/start.png");
	TitleStateTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/titleState.png");
}
void TitleState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		start->HandleEvent();
		if (start->CheckIsHovered())
		{
			std::cout << "changing to game state" << std::endl;
			StateManager::ChangeState(new OfficeState());//change to new game state
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

	SDL_Rect TitleButtonRect = MathManager::ConvertFRect2Rect(start->GetTransform());
	SDL_RenderCopy(pRenderer, m_pStartTexture, nullptr, &TitleButtonRect);
}
void TitleState::Exit()
{
	std::cout << "exiting title state" << std::endl;

	SDL_DestroyTexture(m_pNextTexture);
	m_pNextTexture = nullptr;

	delete next;
	next = nullptr;
}


void OfficeState::Enter()
{

	std::cout << "entering game state" << std::endl;

	next = new UIButton(800, 650, 200, 100);

	//load textures for game state here
	m_pPlayerTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/office/playerPrologue.png");
	m_pTrophyTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/office/prideItem.png");
	m_pWomanWorkerTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/office/womanWorker.png");
	m_pMaleWorkerTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/office/maleOfficeWorker.png");
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/office/officebackground.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/office/officeText.png");
	m_pNextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/continue.png");
}	
void OfficeState::Update(float deltaTime)
{

	if (EventManager::MousePressed(1))
	{
		next->HandleEvent();
		if (next->CheckIsHovered())
		{
			std::cout << "changing to street state" << std::endl;
			StateManager::ChangeState(new StreetState());//change to new game state
		}
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

	SDL_Rect continueRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(pRenderer, m_pNextTexture, nullptr, &continueRect);
 
}
void OfficeState::Resume()
{
	std::cout << "resuming office state" << std::endl;
}
void OfficeState::Exit()
{
	std::cout << "exiting office state" << std::endl;


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

	SDL_DestroyTexture(m_pNextTexture);
	m_pNextTexture = nullptr;

	delete next;
	next = nullptr;

}

void StreetState::Enter()
{
	std::cout << "entering street state.. " << std::endl;

	m_pBackground = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/street/streetBackground.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/street/streetText.png");
	m_pNextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/continue.png");
	next = new UIButton(800, 650, 200, 100);
}

void StreetState::Update(float deltaTime)
{

	if (EventManager::MousePressed(1))
	{
		next->HandleEvent();
		if (next->CheckIsHovered())
		{
			std::cout << "changing to street state" << std::endl;
			StateManager::ChangeState(new CarState());//change to new car state
		}
	}
}

void StreetState::Render()
{
	std::cout << "rendering street state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0, Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackground, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,150, 600,450 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect continueRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pNextTexture, nullptr, &continueRect);
}

void StreetState::Exit()
{
	std::cout << "exiting street state.." << std::endl;

	SDL_DestroyTexture(m_pBackground);
	m_pBackground = nullptr;

	SDL_DestroyTexture(m_pNextTexture);
	m_pNextTexture = nullptr;

	delete next;
	next = nullptr;

}

void CarState::Enter()
{
	std::cout << "entering car state.." << std::endl;
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/carDash/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/carDash/wrathText.png");
	m_pNextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/continue.png");
	next = new UIButton(800, 650, 200, 100);

}

void CarState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		next->HandleEvent();
		if (next->CheckIsHovered())
		{
			std::cout << "changing to truck state" << std::endl;
			StateManager::ChangeState(new TruckState());//change to new car state
		}
	}

}

void CarState::Render()
{
	std::cout << "rendering car state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 300,50,400,350 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect continueRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pNextTexture, nullptr, &continueRect);


}

void CarState::Exit()
{
	std::cout << "exiting car state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pNextTexture);
	m_pNextTexture = nullptr;

	delete next;
	next = nullptr;

}

void TruckState::Enter()
{
	std::cout << "entering truck state.." << std::endl;

	m_pTruckTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/truck/truck.png");
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/truck/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/prologue/truck/truckText.png");
	m_pNextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/continue.png");
	next = new UIButton(800, 650, 200, 100);

}

void TruckState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		next->HandleEvent();
		if (next->CheckIsHovered())
		{
			std::cout << "changing to street state" << std::endl;
			StateManager::ChangeState(new HellState());//change to new car state
		}
	}

}

void TruckState::Render()
{

	std::cout << "rendering truck state.." << std::endl;

	SDL_Rect truckRect = { 0,10,1200,750 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTruckTexture, NULL, &truckRect);

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 100,500,700,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect continueRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pNextTexture, nullptr, &continueRect);


}

void TruckState::Exit()
{
	std::cout << "exiting truck state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pPressXTexture);
	m_pPressXTexture = nullptr;

	SDL_DestroyTexture(m_pTruckTexture);
	m_pTruckTexture = nullptr;

	delete next;
	next = nullptr;

}

//////////////////CHAPTER 1 STATES START////////////////////////////

void HellState::Enter()
{
	std::cout << "entering hell state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/enterHell/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/enterHell/text.png");
	m_pNextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/next.png");
	next = new UIButton(800, 650, 200, 100);

}

void HellState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		next->HandleEvent();
		if (next->CheckIsHovered())
		{
			std::cout << "changing to casino state" << std::endl;
			StateManager::ChangeState(new CasinoState());//change to new car state
		}
	}

}

void HellState::Render()
{
	std::cout << "rendering Hell state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 200,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect continueRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pNextTexture, nullptr, &continueRect);

}

void HellState::Exit()
{
	std::cout << "exiting hell state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pNextTexture);
	m_pNextTexture = nullptr;

	delete next;
	next = nullptr;

}

void CasinoState::Enter()
{
	std::cout << "entering casino state.. " << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casino/background.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casino/devil.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casino/text.png");
	m_pNextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/next.png");
	next = new UIButton(800, 650, 200, 100);

}

void CasinoState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		next->HandleEvent();
		if (next->CheckIsHovered())
		{
			std::cout << "changing to casino choice state" << std::endl;
			StateManager::ChangeState(new CasinoChoiceState());//change to new car state
		}
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

	SDL_Rect continueRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pNextTexture, nullptr, &continueRect);

}

void CasinoState::Exit()
{
	std::cout << " exiting casino state.. " << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;

	SDL_DestroyTexture(m_pNextTexture);
	m_pNextTexture = nullptr;

	delete next;
	next = nullptr;

}

void CasinoChoiceState::Enter()
{
	std::cout << "entering casino choice state.. " << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casino/background.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casino/devil.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoChoice/text.png");
	m_pPress1Texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoChoice/wrongText.png");
	m_pPress2Texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoChoice/rightText.png");

	m_pOptionTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/blank.png");
	m_pOption2Texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/blank.png");
	option = new UIButton(200, 650, 200, 100);
	option2 = new UIButton(700, 650, 200, 100);

}

void CasinoChoiceState::Update(float deltaTime)
{

	if (EventManager::MousePressed(1))
	{
		option->HandleEvent();
		option2->HandleEvent();
		if (option->CheckIsHovered())
		{
			std::cout << "changing to casino lose state" << std::endl;
			StateManager::ChangeState(new CasinoLoseState());//change to new car state
		}

		else if (option2->CheckIsHovered())
		{
			std::cout << "changing to casino exit state" << std::endl;
			StateManager::ChangeState(new CasinoExitState());//change to new car state
		}
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

	SDL_Rect option2Rect = MathManager::ConvertFRect2Rect(option2->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pOption2Texture, nullptr, &option2Rect);

	SDL_Rect Text2Rect = { 740,680,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pPress2Texture, NULL, &Text2Rect);

	SDL_Rect optionRect = MathManager::ConvertFRect2Rect(option->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pOptionTexture, nullptr, &optionRect);

	SDL_Rect TextRect = { 250,680,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pPress1Texture, NULL, &TextRect);
}

void CasinoChoiceState::Exit()
{
	std::cout << "exiting casino choice state.. " << std::endl;

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

	SDL_DestroyTexture(m_pOptionTexture);
	m_pOptionTexture = nullptr;

	delete option2;
	option2 = nullptr;

	delete option;
	option = nullptr;

}

void CasinoExitState::Enter()
{
	std::cout << "entering casino exit state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoExit/background.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casino/devil.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoExit/text.png");
	m_pNextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/next.png");
	next = new UIButton(800, 650, 200, 100);

}

void CasinoExitState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		next->HandleEvent();
		if (next->CheckIsHovered())
		{
			std::cout << "changing to pride enter state" << std::endl;
			StateManager::ChangeState(new PrideEnterState());
		}
	}


}

void CasinoExitState::Render()
{
	std::cout << "rendering casino exit state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect devilRect = { 300,275,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pDevilTexture, NULL, &devilRect);

	SDL_Rect textRect = { 300,20,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect continueRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pNextTexture, nullptr, &continueRect);

}

void CasinoExitState::Exit()
{
	std::cout << "exiting casino exit state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;

	SDL_DestroyTexture(m_pNextTexture);
	m_pNextTexture = nullptr;

	delete next;
	next = nullptr;

}

void CasinoLoseState::Enter()
{
	std::cout << "entering casino lose state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoExit/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoLose/text.png");
	m_pPlayerTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/casinoLose/player.png");
	m_pMenuTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/menu.png");
	mainMenu = new UIButton(800, 620, 200, 200);

}

void CasinoLoseState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		mainMenu->HandleEvent();
		if (mainMenu->CheckIsHovered())
		{
			std::cout << "changing to menu state" << std::endl;
			StateManager::ChangeState(new TitleState());//change to new title state
		}
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

	SDL_Rect menuRect = MathManager::ConvertFRect2Rect(mainMenu->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pMenuTexture, nullptr, &menuRect);

}

void CasinoLoseState::Exit()
{
	std::cout << "exiting casino lose state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pPlayerTexture);
	m_pPlayerTexture = nullptr;

	SDL_DestroyTexture(m_pMenuTexture);
	m_pMenuTexture = nullptr;

	delete mainMenu;
	mainMenu = nullptr;


}

////////////////////CHAPTER 2 START//////////////////////////////////
void PrideEnterState::Enter()
{
	std::cout << "entering pride enter state.." << std::endl;
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideEnter/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideEnter/text.png");
	m_pNextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/next.png");
	next = new UIButton(800, 650, 200, 100);

}

void PrideEnterState::Update(float deltaTime)
{
		if (EventManager::MousePressed(1))
		{
			next->HandleEvent();
			if (next->CheckIsHovered())
			{
				std::cout << "changing to pride choice state" << std::endl;
				StateManager::ChangeState(new PrideChoiceState());//change to new car state
			}
		}	
}

void PrideEnterState::Render()
{
	std::cout << "rendering pride enter state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,575,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect continueRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pNextTexture, nullptr, &continueRect);

}

void PrideEnterState::Exit()
{
	std::cout << "exiting pride enter state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pNextTexture);
	m_pNextTexture = nullptr;

	delete next;
	next = nullptr;

}

void PrideChoiceState::Enter()
{
	std::cout << "entering pride choice state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideEnter/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideChoice/text.png");
	m_pWrongTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideChoice/wrongText.png");
	m_pRightTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideChoice/rightText.png");

	m_pOptionTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/blank.png");
	option = new UIButton(20, 650, 200, 100);

	m_pOption2Texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/blank.png");
	option2 = new UIButton(800, 650, 200, 100);
}

void PrideChoiceState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		option->HandleEvent();
		option2->HandleEvent();
		if (option->CheckIsHovered())
		{
			std::cout << "changing to casino lose state" << std::endl;
			StateManager::ChangeState(new PrideLoseState());
		}

		else if (option2->CheckIsHovered())
		{
			std::cout << "changing to casino exit state" << std::endl;
			StateManager::ChangeState(new PrideExitState());
		}
	}
}

void PrideChoiceState::Render()
{
	std::cout << "rendering pride choice state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,575,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect optionRect = MathManager::ConvertFRect2Rect(option->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pOptionTexture, nullptr, &optionRect);

	SDL_Rect option2Rect = MathManager::ConvertFRect2Rect(option2->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pOption2Texture, nullptr, &option2Rect);

	SDL_Rect WrongRect = { 50,675,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pWrongTextTexture, NULL, &WrongRect);

	SDL_Rect rightRect = { 825,675,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pRightTextTexture, NULL, &rightRect);

}

void PrideChoiceState::Exit()
{
	std::cout << "exiting pride choice state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pWrongTextTexture);
	m_pWrongTextTexture = nullptr;

	SDL_DestroyTexture(m_pRightTextTexture);
	m_pRightTextTexture = nullptr;

	SDL_DestroyTexture(m_pOptionTexture);
	m_pOptionTexture = nullptr;

	SDL_DestroyTexture(m_pOption2Texture);
	m_pOption2Texture = nullptr;

	delete option;
	option = nullptr;

	delete option2;
	option2 = nullptr;

}

void PrideExitState::Enter()
{
	std::cout << "entering pride exit state.." << std::endl;
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideExit/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideExit/text.png");
	m_pNextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/next.png");
	next = new UIButton(800, 650, 200, 100);

}

void PrideExitState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		next->HandleEvent();
		if (next->CheckIsHovered())
		{
			std::cout << "changing to Lust enter state" << std::endl;
			StateManager::ChangeState(new LustEnterState());//change to new car state
		}
	}
}

void PrideExitState::Render()
{
	std::cout << "rendering pride exit state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,575,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect continueRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pNextTexture, nullptr, &continueRect);

}

void PrideExitState::Exit()
{
	std::cout << "exiting pride exit state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pNextTexture);
	m_pNextTexture = nullptr;

	delete next;
	next = nullptr;

}

void PrideLoseState::Enter()
{
	std::cout << "enter pride lose state.." << std::endl;
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideLose/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideLose/text.png");
	m_pPlayerTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter2/prideLose/player.png");
	m_pMenuTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/menu.png");
	mainMenu = new UIButton(800, 620, 200, 200);

}

void PrideLoseState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		mainMenu->HandleEvent();
		if (mainMenu->CheckIsHovered())
		{
			std::cout << "changing to title state" << std::endl;
			StateManager::ChangeState(new TitleState());//change to new car state
		}
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

	SDL_Rect menuRect = MathManager::ConvertFRect2Rect(mainMenu->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pMenuTexture, nullptr, &menuRect);

}

void PrideLoseState::Exit()
{
	std::cout << "exiting pride lose state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pMenuTexture);
	m_pMenuTexture = nullptr;

	delete mainMenu;
	mainMenu = nullptr;


}

////////////////////CHAPTER 3 START//////////////////////////////////
void LustEnterState::Enter()
{
	std::cout << "entering lust enter state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/LustEnter/text.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/devil.png");
	m_pNextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/next.png");
	next = new UIButton(800, 650, 200, 100);

}

void LustEnterState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		next->HandleEvent();
		if (next->CheckIsHovered())
		{
			std::cout << "changing to lust choice state" << std::endl;
			StateManager::ChangeState(new LustChoiceState());
		}
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

	SDL_Rect continueRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pNextTexture, nullptr, &continueRect);
}

void LustEnterState::Exit()
{
	std::cout << "exiting lust enter state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;

	SDL_DestroyTexture(m_pNextTexture);
	m_pNextTexture = nullptr;

	delete next;
	next = nullptr;

}

void LustChoiceState::Enter()
{
	std::cout << "entering lust choice state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/LustChoice/text.png");
	m_pRightTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/LustChoice/rightText.png");
	m_pWrongTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/LustChoice/wrongText.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/devil.png");

	m_pOptionTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/blank.png");
	option = new UIButton(20, 650, 200, 100);

	m_pOption2Texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/blank.png");
	option2 = new UIButton(800, 650, 200, 100);

}

void LustChoiceState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		option->HandleEvent();
		option2->HandleEvent();
		if (option->CheckIsHovered())
		{
			std::cout << "changing to casino lose state" << std::endl;
			StateManager::ChangeState(new LustExitState());
		}

		else if (option2->CheckIsHovered())
		{
			std::cout << "changing to casino exit state" << std::endl;
			StateManager::ChangeState(new LustLoseState());
		}
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

	SDL_Rect optionRect = MathManager::ConvertFRect2Rect(option->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pOptionTexture, nullptr, &optionRect);

	SDL_Rect option2Rect = MathManager::ConvertFRect2Rect(option2->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pOption2Texture, nullptr, &option2Rect);

	SDL_Rect rightRect = { 50,670,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pRightTextTexture, NULL, &rightRect);

	SDL_Rect wrongRect = { 840,670,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pWrongTextTexture, NULL, &wrongRect);

}

void LustChoiceState::Exit()
{
	std::cout << "exiting lust choice state" << std::endl;


	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pWrongTextTexture);
	m_pWrongTextTexture = nullptr;

	SDL_DestroyTexture(m_pRightTextTexture);
	m_pRightTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;

	SDL_DestroyTexture(m_pOptionTexture);
	m_pOptionTexture = nullptr;

	delete option;
	option = nullptr;
	
	SDL_DestroyTexture(m_pOption2Texture);
	m_pOption2Texture = nullptr;

	delete option2;
	option2 = nullptr;

}

void LustExitState::Enter()
{
	std::cout << "entering lust exit state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/lustExit/text.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/devil.png");
	m_pNextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/next.png");
	next = new UIButton(800, 650, 200, 100);


}

void LustExitState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		next->HandleEvent();
		if (next->CheckIsHovered())
		{
			std::cout << "changing to enevy enter state" << std::endl;
			StateManager::ChangeState(new EnvyEnterState());//change to new car state
		}
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

	SDL_Rect continueRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pNextTexture, nullptr, &continueRect);

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

	SDL_DestroyTexture(m_pNextTexture);
	m_pNextTexture = nullptr;

	delete next;
	next = nullptr;

}

void LustLoseState::Enter()
{
	std::cout << "entering lust lose state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/lustLose/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter3/lustLose/text.png");
	m_pMenuTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/main.png");
	mainMenu = new UIButton(800, 650, 200, 100);

}

void LustLoseState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		mainMenu->HandleEvent();
		if (mainMenu->CheckIsHovered())
		{
			std::cout << "changing to title state" << std::endl;
			StateManager::ChangeState(new TitleState());
		}
	}

}

void LustLoseState::Render()
{
	std::cout << "rendering lust lose state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect menuRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pMenuTexture, nullptr, &menuRect);

}

void LustLoseState::Exit()
{
	std::cout << "exiting lust lose state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;


	SDL_DestroyTexture(m_pMenuTexture);
	m_pMenuTexture = nullptr;

	delete mainMenu;
	mainMenu = nullptr;

}
////////////////////CHAPTER 4 START//////////////////////////////////

void EnvyEnterState::Enter()
{
	std::cout << "entering envy enter state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/envyEnter/text.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/devil.png");
	m_pNextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/next.png");
	next = new UIButton(800, 650, 200, 100);

}

void EnvyEnterState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		next->HandleEvent();
		if (next->CheckIsHovered())
		{
			std::cout << "changing to envy choice state" << std::endl;
			StateManager::ChangeState(new EnvyChoiceState());//change to new car state
		}
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

	SDL_Rect continueRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pNextTexture, nullptr, &continueRect);

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

	SDL_DestroyTexture(m_pNextTexture);
	m_pNextTexture = nullptr;

	delete next;
	next = nullptr;
}

void EnvyChoiceState::Enter()
{
	std::cout << "entering envy choice state.. " << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/envyChoice/text.png");
	m_pWrongTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/envyChoice/wrongText.png");
	m_pRightTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/envyChoice/rightText.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/devil.png");

	m_pOptionTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/blank.png");
	option = new UIButton(20, 650, 200, 100);

	m_pOption2Texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/blank.png");
	option2 = new UIButton(800, 650, 200, 100);

}

void EnvyChoiceState::Update(float deltaTime)
{

	if (EventManager::MousePressed(1))
	{
		option->HandleEvent();
		option2->HandleEvent();
		if (option->CheckIsHovered())
		{
			std::cout << "changing to envy lose state" << std::endl;
			StateManager::ChangeState(new EnvyLoseState());//change to new car state
		}

		else if (option2->CheckIsHovered())
		{
			std::cout << "changing to envy exit state" << std::endl;
			StateManager::ChangeState(new EnvyExitState());//change to new car state
		}
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

	SDL_Rect optionRect = MathManager::ConvertFRect2Rect(option->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pOptionTexture, nullptr, &optionRect);

	SDL_Rect option2Rect = MathManager::ConvertFRect2Rect(option2->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pOption2Texture, nullptr, &option2Rect);

	SDL_Rect wrongRect = { 40,680,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pWrongTextTexture, NULL, &wrongRect);

	SDL_Rect rightRect = { 820,680,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pRightTextTexture, NULL, &rightRect);

}

void EnvyChoiceState::Exit()
{
	std::cout << "exiting envy choice state" << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pWrongTextTexture);
	m_pWrongTextTexture = nullptr;

	SDL_DestroyTexture(m_pRightTextTexture);
	m_pRightTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;

	SDL_DestroyTexture(m_pOptionTexture);
	m_pOptionTexture = nullptr;

	delete option;
	option = nullptr;

	SDL_DestroyTexture(m_pOption2Texture);
	m_pOption2Texture = nullptr;

	delete option2;
	option2 = nullptr;


}

void EnvyExitState::Enter()
{
	std::cout << "entering envy exit state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/envyExit/text.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/devil.png");
	m_pNextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/next.png");
	next = new UIButton(800, 650, 200, 100);

}

void EnvyExitState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		next->HandleEvent();
		if (next->CheckIsHovered())
		{
			std::cout << "changing to wrath enter state" << std::endl;
			StateManager::ChangeState(new WrathEnterState());
		}
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

	SDL_Rect continueRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pNextTexture, nullptr, &continueRect);

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

	SDL_DestroyTexture(m_pNextTexture);
	m_pNextTexture = nullptr;

	delete next;
	next = nullptr;

}

void EnvyLoseState::Enter()
{
	std::cout << "entering envy lose state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter4/envyLose/text.png");
	m_pMenuTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/menu.png");
	mainMenu = new UIButton(800, 620, 200, 200);

}

void EnvyLoseState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		mainMenu->HandleEvent();
		if (mainMenu->CheckIsHovered())
		{
			std::cout << "changing to title state" << std::endl;
			StateManager::ChangeState(new TitleState());
		}
	}

}

void EnvyLoseState::Render()
{
	std::cout << "rendering envy lose state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,300,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect menuRect = MathManager::ConvertFRect2Rect(mainMenu->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pMenuTexture, nullptr, &menuRect);


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
	m_pNextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/next.png");
	next = new UIButton(800, 650, 200, 100);

}

void WrathEnterState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		next->HandleEvent();
		if (next->CheckIsHovered())
		{
			std::cout << "changing to wrath choice state" << std::endl;
			StateManager::ChangeState(new WrathChoiceState());
		}
	}
}

void WrathEnterState::Render()
{
	std::cout << "rendering wrath enter state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect continueRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pNextTexture, nullptr, &continueRect);
}

void WrathEnterState::Exit()
{
	std::cout << "exiting wrath enter state" << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pNextTexture);
	m_pNextTexture = nullptr;

	delete next;
	next = nullptr;


}

void WrathChoiceState::Enter()
{
	std::cout << "entering wrath choice state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter5/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter5/wrathChoice/text.png");
	m_pRightTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter5/wrathChoice/rightText.png");
	m_pWrongTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter5/wrathChoice/wrongText.png");

	m_pOptionTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/blank.png");
	option = new UIButton(20, 650, 200, 100);

	m_pOption2Texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/blank.png");
	option2 = new UIButton(800, 650, 200, 100);

}

void WrathChoiceState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		option->HandleEvent();
		option2->HandleEvent();
		if (option->CheckIsHovered())
		{
			std::cout << "changing to wrath exit state" << std::endl;
			StateManager::ChangeState(new WrathExitState());
		}

		else if (option2->CheckIsHovered())
		{
			std::cout << "changing to wrath lose state" << std::endl;
			StateManager::ChangeState(new WrathLoseState());
		}
	}

}

void WrathChoiceState::Render()
{
	std::cout << "rendering wrath choice state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect optionRect = MathManager::ConvertFRect2Rect(option->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pOptionTexture, nullptr, &optionRect);

	SDL_Rect option2Rect = MathManager::ConvertFRect2Rect(option2->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pOption2Texture, nullptr, &option2Rect);

	SDL_Rect rightRect = { 30,680,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pRightTextTexture, NULL, &rightRect);

	SDL_Rect wrongRect = { 840,680,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pWrongTextTexture, NULL, &wrongRect);
}

void WrathChoiceState::Exit()
{
	std::cout << "exiting wrath choice state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pRightTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pWrongTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pOptionTexture);
	m_pOptionTexture = nullptr;

	delete option;
	option = nullptr;

	SDL_DestroyTexture(m_pOption2Texture);
	m_pOption2Texture = nullptr;

	delete option2;
	option2 = nullptr;
}

void WrathExitState::Enter()
{
	std::cout << "entering wrath exit state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter5/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter5/wrathExit/text.png");
	m_pNextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter1/next.png");
	next = new UIButton(800, 650, 200, 100);

}

void WrathExitState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		next->HandleEvent();
		if (next->CheckIsHovered())
		{
			std::cout << "changing to gluttony enter state" << std::endl;
			StateManager::ChangeState(new GluttonyEnterState());
		}
	}
}

void WrathExitState::Render()
{
	std::cout << "rendering wrath exit state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect continueRect = MathManager::ConvertFRect2Rect(next->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pNextTexture, nullptr, &continueRect);

}

void WrathExitState::Exit()
{
	std::cout << "exiting wrath exit state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pNextTexture);
	m_pNextTexture = nullptr;

	delete next;
	next = nullptr;

}

void WrathLoseState::Enter()
{
	std::cout << "entering wrath lose state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter5/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter5/wrathLose/text.png");
	m_pPlayerTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter5/wrathLose/player.png");
	m_pMenuTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/menu.png");
	mainMenu = new UIButton(800, 620, 200, 200);

}

void WrathLoseState::Update(float deltaTime)
{
	if (EventManager::MousePressed(1))
	{
		mainMenu->HandleEvent();
		if (mainMenu->CheckIsHovered())
		{
			std::cout << "changing to title state" << std::endl;
			StateManager::ChangeState(new TitleState());
		}
	}

}

void WrathLoseState::Render()
{
	std::cout << "rendering wrath lose state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect playerRect = { 300,300,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pPlayerTexture, NULL, &playerRect);

	SDL_Rect menuRect = MathManager::ConvertFRect2Rect(mainMenu->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pMenuTexture, nullptr, &menuRect);

}

void WrathLoseState::Exit()
{
	std::cout << "exiting wrath lose state" << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pPlayerTexture);
	m_pPlayerTexture = nullptr;

	SDL_DestroyTexture(m_pMenuTexture);
	m_pMenuTexture = nullptr;

	delete mainMenu;
	mainMenu = nullptr;

}
////////////////////CHAPTER 6 START//////////////////////////////////
void GluttonyEnterState::Enter()
{
	std::cout << "entering gluttony enter state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter6/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter6/gluttonyEnter/text.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter6/devil.png");
}

void GluttonyEnterState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_C))
	{
		std::cout << "changing to gluttony choice state" << std::endl;
		StateManager::ChangeState(new GluttonyChoiceState());
	}
}

void GluttonyEnterState::Render()
{
	std::cout << "rendering gluttony enter state.." << std::endl;


	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect devilRect = { 700,350,300,300 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pDevilTexture, NULL, &devilRect);
}

void GluttonyEnterState::Exit()
{
	std::cout << "exiting gluttony enter state.." << std::endl;

		SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;
}

void GluttonyChoiceState::Enter()
{
	std::cout << "entering gluttony choice state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter6/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter6/gluttonyChoice/text.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter6/devil.png");
}

void GluttonyChoiceState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_1))
	{
		std::cout << "changing to gluttony exit state" << std::endl;
		StateManager::ChangeState(new GluttonyExitState());
	}

	else if (Game::GetInstance().KeyDown(SDL_SCANCODE_2))
	{
		std::cout << "changing to gluttony lose state" << std::endl;
		StateManager::ChangeState(new GluttonyLoseState());
	}
}

void GluttonyChoiceState::Render()
{
	std::cout << "rendering gluttony choice state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect devilRect = { 350,350,300,300 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pDevilTexture, NULL, &devilRect);
}

void GluttonyChoiceState::Exit()
{
	std::cout << "exiting gluttony choice state.." << std::endl;


	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;
}

void GluttonyExitState::Enter()
{
	std::cout << "entering gluttony exit state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter6/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter6/gluttonyExit/text.png");
}

void GluttonyExitState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_C))
	{
		std::cout << "changing to sloth enter state" << std::endl;
		StateManager::ChangeState(new SlothEnterState());
	}
}

void GluttonyExitState::Render()
{
	std::cout << "rendering gluttony exit state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);
}

void GluttonyExitState::Exit()
{
	std::cout << "exiting gluttony exit state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;
}

void GluttonyLoseState::Enter()
{
	std::cout << "entering gluttony lose state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter6/background.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter6/devil.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter6/gluttonyLose/text.png");
}

void GluttonyLoseState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_R))
	{
		std::cout << "changing to casino choice state" << std::endl;
		StateManager::ChangeState(new TitleState());
	}
}

void GluttonyLoseState::Render()
{
	std::cout << "rendering gluttony lose state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 250,50,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect devilRect = { 350,350,300,300 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pDevilTexture, NULL, &devilRect);
}

void GluttonyLoseState::Exit()
{
	std::cout << "exiting gluttony lose state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;
}

////////////////////CHAPTER 7 START//////////////////////////////////
void SlothEnterState::Enter()
{
	std::cout << "entering first sloth state.." << std::endl;
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/background.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/devil.png");
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
	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/background.png");
	m_pDevilTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/devil.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/slothChoice/text.png");
}

void SlothChoiceState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_1))
	{
		std::cout << "changing to gluttony exit state" << std::endl;
		StateManager::ChangeState(new SlothExitState());
	}

	else if (Game::GetInstance().KeyDown(SDL_SCANCODE_2))
	{
		std::cout << "changing to gluttony lose state" << std::endl;
		StateManager::ChangeState(new SlothLoseState());
	}
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

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pDevilTexture);
	m_pDevilTexture = nullptr;
}

void SlothExitState::Enter()
{
	std::cout << "entering sloth exit state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/slothExit/text.png");
}

void SlothExitState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_C))
	{
		std::cout << "changing to epilogue state" << std::endl;
		StateManager::ChangeState(new EpilogueState());
	}
}

void SlothExitState::Render()
{
	std::cout << "rendering sloth exit state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 300,300,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);
}

void SlothExitState::Exit()
{
	std::cout << "exiting sloth exit state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;
}

void SlothLoseState::Enter()
{
	std::cout << "entering sloth lose state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/slothLose/text.png");
	m_pPlayerTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/chapter7/slothLose/player.png");
}

void SlothLoseState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_R))
	{
		std::cout << "changing to menu state" << std::endl;
		StateManager::ChangeState(new TitleState());
	}
}

void SlothLoseState::Render()
{
	std::cout << "rendering sloth lose state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 300,20,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect playerRect = { 400,320,200,200 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pPlayerTexture, NULL, &playerRect);
}

void SlothLoseState::Exit()
{
	std::cout << "exiting sloth lose state.." << std::endl;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pPlayerTexture);
	m_pPlayerTexture = nullptr;
}
//////////////////////epilogue//////////////////////////////////

void EpilogueState::Enter()
{
	std::cout << "entering epilogue state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/epilogue/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/epilogue/text.png");
	m_pPortalTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/epilogue/portal.png");
}

void EpilogueState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_C))
	{
		std::cout << "changing to win state" << std::endl;
		StateManager::ChangeState(new WinState());
	}
}

void EpilogueState::Render()
{
	std::cout << "rendering epilogue state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 300,20,500,500 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect portalRect = { 400,450,200,200 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pPortalTexture, NULL, &portalRect);
}

void EpilogueState::Exit()
{
	std::cout << "exiting epilogue state.." << std::endl;

	SDL_DestroyTexture(m_pTextTexture);
	m_pTextTexture = nullptr;

	SDL_DestroyTexture(m_pBackgroundTexture);
	m_pBackgroundTexture = nullptr;
}

void WinState::Enter()
{
	std::cout << "entering win state.." << std::endl;

	m_pBackgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/win/background.png");
	m_pTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/win/text.png");
	m_pWinTextTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/win/wintext.png");
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
	std::cout << "rendering win state.." << std::endl;

	SDL_Rect backgroundRect = { 0,0,Game::kWidth,Game::kHeight };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pBackgroundTexture, NULL, &backgroundRect);

	SDL_Rect textRect = { 270,300,600,600 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pTextTexture, NULL, &textRect);

	SDL_Rect winRect = { 350,20,600,600 };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_pWinTextTexture, NULL, &winRect);
}
void WinState::Exit()
{
	std::cout << "exiting lose state.." << std::endl;
}