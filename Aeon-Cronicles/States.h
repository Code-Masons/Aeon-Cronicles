#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include <vector>
#include<string>
#include <map>
#include "GameObject.h"
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
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;

};

class GameState : public State//main game loop screen
{
	static const int kPlayerSpeed = 200;
	SDL_FRect m_rectangleTransform;

	//game objects 
	GameObject* m_player;
	GameObject* m_enemy;

	//textures
	SDL_Texture* m_pPlayerTexture;
	SDL_Texture* m_pEnemyTexture;

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

class LoseState : public State//pause screen
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};



