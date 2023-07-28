#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include <vector>
#include<string>
#include <map>
#include "GameObject.h"
#include "Game.h"

class State
{
public:
	State() = default;
	virtual ~State() = default;
	//static Game& GetInstance();
	//criteria for each state each state MUST have the following 
	virtual void Enter() = 0;//use for initialization of assets
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;// use to render assets
	virtual void Exit() = 0;//use to destroy assets
	virtual void Resume() { }

	//std::map<std::string, GameObject*> m_objects;
};

class TitleState : public State//main menu screen
{
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
	 int lWidth = 2500;
	 int lHeight = Game::kHeight;
	static const int kPlayerSpeed = 200;
	static const int kEnemySpeed = 80;
	static const int kPlayerJumpForce = -1000;
	SDL_Rect camera = { 0,0, Game::kWidth, Game::kHeight };
	SDL_FRect m_rectangleTransform;

	//game objects 
	GameObject* m_player;
	GameObject* m_womanWorker;
	GameObject* m_maleWorker;
	GameObject* m_trophy;
	GameObject* m_text;
	GameObject* m_continue;

	GameObject* m_background;

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

	GameObject* m_background;
	GameObject* m_text;
	GameObject* m_continue;

	SDL_Texture* m_pContinueTexture;
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
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class LoseState : public State//lose screen
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};



