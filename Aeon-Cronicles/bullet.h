#pragma once
#include <vector>
#include <SDL.h>

class bullet
{
public:

	float bulletDelay = 0.5f;
	std::vector velocity;
	sprite sprite;

	void playerShoot();
	void enemyShoot();
	void Update();
	void spawnBullet();

private:
	float bulletTimer = 0.0f;

};

