#include "bullet.h"
#include "spawnBullet.h"
#include "GameObject.h"
#include "Game.h"
#include <vector>
#include <iostream>

SDL_Renderer* pRenderer = NULL;

namespace Game
{
	struct vec2
	{
		float x = 0;
		float y = 0;
	};

	struct sprite
	{
	private:
		SDL_Texture* pTexture;
		SDL_Rect Src;
		SDL_Rect Dst;

	public:
		int animationframecount = 1;
		float animationcurrentframe = 0;
		vec2 position;
		double rotation = 0.0;
		SDL_RendererFlip flipstate = SDL_FLIP_NONE;

		sprite()
		{
			std::cout << "sprite default constructor!" << std::endl;
			pTexture = nullptr;
			Src = { 0,0,0,0 };
			Dst = { 0,0,0,0 };
		}

		// A non-default constructor can take arguments
		sprite(SDL_Renderer* renderer, const char* imagefilepath)
		{
			
			Src.x = 0;
			Src.y = 0;

			Dst.x = 0;
			Dst.y = 0;
			Dst.w = Src.w;
			Dst.h = Src.h;
		}
		sprite(SDL_Renderer* renderer, const char* imagefilepath, int framewidth, int frameheight, int numberofframesinsheet) :sprite(renderer, imagefilepath)
		{
			Src.w = framewidth;
			Src.h = frameheight;
			Dst.w = framewidth;
			Dst.h = frameheight;
			animationframecount = numberofframesinsheet;
		}

		void SetPosition(int x, int y)
		{
			position.x = x;
			position.y = y;
		}
		void setsize(int x, int y)
		{
			Dst.w = x;
			Dst.h = y;
		}
		SDL_Rect GetRect() const//const keyword says "this function does not anythig about class"
		{
			SDL_Rect returnvalue = Dst;
			returnvalue.x = position.x;
			returnvalue.y = position.y;
			return Dst;
		}
		vec2 Getsize() const
		{
			vec2 sizeXY = { Dst.w,Dst.h };
			return sizeXY;
		}
		void CleanUp()
		{
			SDL_DestroyTexture(pTexture);
		}
	};
}


void playerShoot(bool towardright, std::vector<bullet>& container, Game::vec2 velocity)
{
	Game::sprite bulletsprite = Game::sprite(pRenderer, "../Assets/textures/playerbullet.png");

	//set bullets start position
	bulletsprite.position.x = sprite.position.x;
	if (towardright)
	{
		bulletsprite.position.x += sprite.Getsize().x;
	}

	bulletsprite.position.y = sprite.position.y + (GameObject.Getsize().y / 2);


	bullet bullet;
	bullet.sprite = bulletsprite;
	bullet.velocity = velocity;
	//add bullets to our dynamic array of bullets
	container.push_back(bullet);
	//reset cooldown timer
	bulletTimer = bulletDelay;
}

void EnemyShoot(bool towardright, std::vector<projectile>& container, Game::vec2 velocity)
{
	GameObject::GameObject bulletsprite = GameObject::GameObject(pRenderer, "../Assets/textures/enemybullet.png"
		//set bullets start position
		bulletsprite.position.x = GameObject.position.x;
	if (towardright)
	{
		bulletsprite.position.x += GameObject.Getsize().x;
	}

	bulletsprite.position.y = GameObject.position.y + (GameObject.Getsize().y / 2);


	bullet bullet;
	bullet.sprite = bulletsprite;
	bullet.velocity = velocity;
	add bullets to our dynamic array of bullets
		container.push_back(projectile);
	//reset cooldown timer
	bulletTimer = bulletDelay;
}

void Update()
{
	GameObject.position.x += velocity.x * deltatime;
	GameObject.position.y += velocity.y * deltatime;
}