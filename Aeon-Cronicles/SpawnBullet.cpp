//
//#include "spawnBullet.h"
//#include "GameObject.h"
//#include "Game.h"
//
//
//void playerShoot(bool towardright, std::vector<projectile>& container, Game::vec2 velocity)
//{
//	Game::sprite projectilesprite = Game::sprite(pRenderer, "../Assets/textures/dotforp.png");
//
//	//set bullets start position
//	projectilesprite.position.x = sprite.position.x;
//	if (towardright)
//	{
//		projectilesprite.position.x += sprite.Getsize().x; //- projectilesprite.Getsize().x;
//	}
//
//	projectilesprite.position.y = sprite.position.y + (sprite.Getsize().y / 2);//-(projectilesprite.Getsize().y/2);
//
//
//	projectile projectile;
//	projectile.sprite = projectilesprite;
//	projectile.velocity = velocity;
//	//add bullets to our dynamic array of bullets
//	container.push_back(projectile);
//	//reset cooldown timer
//	firerepeattimer = firerepeatdelay;
//}
//void EnemyShoot(bool towardright, std::vector<projectile>& container, Game::vec2 velocity)
//{
//	Game::sprite projectilesprite = Game::sprite(pRenderer, "../Assets/textures/Rdotfore.png");
//	//set bullets start position
//	projectilesprite.position.x = sprite.position.x;
//	if (towardright)
//	{
//		projectilesprite.position.x += sprite.Getsize().x; //- projectilesprite.Getsize().x;
//	}
//
//	projectilesprite.position.y = sprite.position.y + (sprite.Getsize().y / 2);//-(projectilesprite.Getsize().y/2);
//
//
//	projectile projectile;
//	projectile.sprite = projectilesprite;
//	projectile.velocity = velocity;
//	//add bullets to our dynamic array of bullets
//	container.push_back(projectile);
//	//reset cooldown timer
//	firerepeattimer = firerepeatdelay;
//}