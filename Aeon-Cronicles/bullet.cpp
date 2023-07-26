#include "bullet.h"
#include "spawnBullet.h"
#include "GameObject.h"
#include "Game.h"


void playerShoot(bool towardright, std::vector<projectile>& container, Game::vec2 velocity)
{
	GameObject::GameObject bulletsprite = Game::GameObject(pRenderer, "../Assets/textures/playerbullet.png");

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