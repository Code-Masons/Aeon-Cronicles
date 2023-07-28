#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include <vector>
#include <string>
#include <map>
#include "GameObject.h"
#include "tilelevel.h"
#include "Game.h"
#include "UI_Button.h"
#include "StateManager.h"

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
	UIButton* StartGameButton;
	SDL_Texture* StartGameButtonTexture;
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;

};

class GameState : public State//main game loop screen
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
	GameObject* m_enemy;

	TileLevel* tileLevel;

	GameObject* m_background;


	//textures
	SDL_Texture* m_pPlayerTexture;
	SDL_Texture* m_pEnemyTexture;
	SDL_Texture* m_pBackgroundTexture;

	//Mix_Music* m_pMusic;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Resume() override;
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
	//UIButton* RetryButton;
	//SDL_Texture* RetryButtonTexture;

	UIButton* MainMenuButton;
	SDL_Texture* MainMenuButtonTexture;
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class LoseState : public State//lose screen
{
	//UIButton* RetryButton;
	//SDL_Texture* RetryButtonTexture;

	UIButton* MainMenuButton;
	SDL_Texture* MainMenuButtonTexture;
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};



