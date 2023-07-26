#include "Bullet.h"
#include "GameObject.h"
#include "Game.h"
#include "main.cpp"
#include "Sprite.h"


void playerShoot(bool towardright, std::vector<Bullet>& container, Game::vec2 velocity)
{
	Game::Sprite bulletSprite = Game::sprite(pRenderer, "../Assets/textures/dotforp.png");
	/
	//set bullets start position
	bulletSprite.position.x = sprite.position.x;
	if (towardright)
	{
		bulletSprite.position.x += sprite.Getsize().x; //- projectilesprite.Getsize().x;
	}

	bulletSprite.position.y = sprite.position.y + (sprite.Getsize().y / 2);//-(projectilesprite.Getsize().y/2);


	Bullet bullet;
	bullet.sprite = bulletSprite;
	bullet.velocity = velocity;
	//add bullets to our dynamic array of bullets
	container.push_back(bullet);
	//reset cooldown timer
	firerepeattimer = firerepeatdelay;
}
void EnemyShoot(bool towardright, std::vector<Bullet>& container, Game::vec2 velocity)
{
	Game::sprite bulletSprite = Game::sprite(pRenderer, "../Assets/textures/Rdotfore.png");
	//set bullets start position
	bulletSprite.position.x = sprite.position.x;
	if (towardright)
	{
		bulletSprite.position.x += sprite.Getsize().x; //- projectilesprite.Getsize().x;
	}

	bulletSprite.position.y = sprite.position.y + (sprite.Getsize().y / 2);//-(projectilesprite.Getsize().y/2);


	Bullet bullet;
	bullet.sprite = bulletSprite;
	bullet.velocity = velocity;
	//add bullets to our dynamic array of bullets
	container.push_back(bullet);
	//reset cooldown timer
	firerepeattimer = firerepeatdelay;
}