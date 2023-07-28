#pragma once
#include "SDL.h"
#include "GameObject.h"
class Sprite //: public GameObject
{
protected:
	SDL_Rect m_sourceTransform;
	SDL_FRect m_destinationTransform;
	int m_angle;
public:
	Sprite();
	//Sprite(SDL_Rect sourceTransform, SDL_FRect destinationTransform);
	Sprite(SDL_Rect sourceTransform, SDL_FRect destinationTransform, int angle);
	SDL_Rect& GetSourceTransform() { return m_sourceTransform; }
	SDL_FRect& GetDestinationTransform() { return m_destinationTransform; }
	int GetAngle() { return m_angle; }

};

