#pragma once
#ifndef __BULLETSPAWN_H__
#define __BULLETSPAWN_H__
#include <SDL.h>
#include "GameObject.h"

class BulletSpawn : public GameObject
{
private:
	double m_dx, m_dy;
	static const float s_speed;
	SDL_FRect m_dst;
public:
	BulletSpawn(const SDL_FRect, const double, const double);
	void Update();
	void Render();
	// bool deleteMe; // Flag that will let the program know, we can delete it.

};

#endif
