#include "Sprite.h"

Sprite::Sprite()
	:m_sourceTransform{ 0, 0, 0, 0 }
	, m_destinationTransform{ 0, 0, 0, 0 }
	, m_angle{ 0 }
{

}
Sprite::Sprite(SDL_Rect sourceTranform, SDL_FRect destinationTransform, int angle)
	:m_sourceTransform{ sourceTranform }
	, m_destinationTransform{ destinationTransform }
	, m_angle{ angle }
{

}