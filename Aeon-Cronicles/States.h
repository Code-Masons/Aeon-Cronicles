#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include <vector>
#include<string>
#include <map>
#include "GameObject.h"
#include "Game.h"
#include "UI_Button.h"

class State
{
public:
	State() = default;
	virtual ~State() = default;

	UIButton* next;
	SDL_Texture* m_pNextTexture;

	UIButton* option;
	SDL_Texture* m_pOptionTexture;
	
	UIButton* option2;
	SDL_Texture* m_pOption2Texture;

	UIButton* mainMenu;
	SDL_Texture* m_pMenuTexture;

	

	//static Game& GetInstance();
	//criteria for each state each state MUST have the following 
	virtual void Enter() = 0;//use for initialization of assets
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;// use to render assets
	virtual void Exit() = 0;//use to destroy assets
	virtual void Resume() { }

};

class TitleState : public State//main menu screen
{
	UIButton* start;
	SDL_Texture* m_pStartTexture;

	GameObject* GameName;
	SDL_Texture* TitleStateTexture;
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;

};

class OfficeState : public State//first scene of prologue
{
	//textures
	SDL_Texture* m_pPlayerTexture;
	SDL_Texture* m_pWomanWorkerTexture;
	SDL_Texture* m_pMaleWorkerTexture;
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTrophyTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pContinueTexture;

	//Mix_Music* m_pMusic;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Resume() override;
};

class StreetState : public State//win screen
{
	SDL_Texture* m_pBackground;
	SDL_Texture* m_pTextTexture;
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};


class CarState : public State//win screen
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;	

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;

};

class TruckState : public State//win screen
{
	GameObject* m_background;
	GameObject* m_text;
	GameObject* m_truck;
	GameObject* m_pressX;

	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pTruckTexture;
	SDL_Texture* m_pPressXTexture;
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;

};


///////////////CHAPTER 1 STATES//////////////////////
class HellState : public State//hell start screen
{

	GameObject* m_background;
	GameObject* m_Text;
	GameObject* m_PressC;

	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pPressCTexture;
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class CasinoState : public State
{
public:

	GameObject* m_background;
	GameObject* m_devil;
	GameObject* m_text;
	GameObject* m_pressX;

	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pDevilTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pPressXTexture;


	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class CasinoChoiceState : public State
{

	GameObject* m_background;
	GameObject* m_devil;
	GameObject* m_text;
	GameObject* m_press1;
	GameObject* m_press2;

	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pDevilTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pPress1Texture;
	SDL_Texture* m_pPress2Texture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};


class CasinoExitState : public State
{

	GameObject* m_background;
	GameObject* m_devil;
	GameObject* m_text;

	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pDevilTexture;
	SDL_Texture* m_pTextTexture;


public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class CasinoLoseState : public State
{

	GameObject* m_background;
	GameObject* m_text;
	GameObject* m_player;

	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pPlayerTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

//////////////////////////CHAPTER 2////////////////////////////// 
class PrideEnterState : public State
{

	GameObject* m_background;
	GameObject* m_text;
	
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class PrideChoiceState : public State
{

	GameObject* m_background;
	GameObject* m_text;

	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pWrongTextTexture;
	SDL_Texture* m_pRightTextTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class PrideExitState : public State
{

	GameObject* m_background;
	GameObject* m_text;

	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class PrideLoseState : public State
{

	GameObject* m_background;
	GameObject* m_text;
	GameObject* m_player;

	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pPlayerTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

//////////////////////////CHAPTER 7////////////////////////////// 
class LustEnterState : public State//lust screen
{

	GameObject* m_background;
	GameObject* m_text;
	GameObject* m_devil;

	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pDevilTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class LustChoiceState : public State
{

	GameObject* m_background;
	GameObject* m_text;
	GameObject* m_devil;

	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pRightTextTexture;
	SDL_Texture* m_pWrongTextTexture;
	SDL_Texture* m_pDevilTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class LustExitState : public State
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pDevilTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class LustLoseState : public State
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pDevilTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};
//////////////////////////CHAPTER 4////////////////////////////// 
class EnvyEnterState : public State
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pDevilTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class EnvyChoiceState : public State
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pDevilTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class EnvyExitState : public State
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pDevilTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class EnvyLoseState : public State
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};
//////////////////////////CHAPTER 7////////////////////////////// 
class WrathEnterState : public State
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class WrathChoiceState : public State
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class WrathExitState : public State
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class WrathLoseState : public State
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pPlayerTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

//////////////////////////CHAPTER 6////////////////////////////// 
class GluttonyEnterState : public State
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pDevilTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class GluttonyChoiceState : public State
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pDevilTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class GluttonyExitState : public State
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class GluttonyLoseState : public State
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pDevilTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

//////////////////////////CHAPTER 7////////////////////////////// 
class SlothEnterState : public State//chapter 7 start screen
{
	GameObject* m_background;
	GameObject* m_devil;
	GameObject* m_text;

	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pDevilTexture;
	SDL_Texture* m_pTextTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class SlothChoiceState : public State//chapter 7 start screen
{
	GameObject* m_background;
	GameObject* m_devil;
	GameObject* m_text;

	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pDevilTexture;
	SDL_Texture* m_pTextTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class SlothExitState : public State//chapter 7 start screen
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class SlothLoseState : public State//chapter 7 start screen
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pPlayerTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class EpilogueState : public State//chapter 7 start screen
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pPortalTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class PauseState : public State//pause screen
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class WinState : public State//win screen
{
	SDL_Texture* m_pBackgroundTexture;
	SDL_Texture* m_pTextTexture;
	SDL_Texture* m_pWinTextTexture;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};



