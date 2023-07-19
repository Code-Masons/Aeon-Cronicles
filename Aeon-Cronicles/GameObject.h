#pragma once
#include <SDL.h>

class GameObject
{
public:
	GameObject(float x, float y, float w, float h, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255);

	void Draw(SDL_Renderer* pRenderer);
	float UpdatePositionX(float x);
	float UpdatePositionY(float y);
	float GetObjectWidth();
	float GetObjectHeight();

	//virtual void Update(float deltaTime) = 0;
	//virtual void Render() = 0;

	SDL_FRect& GetTransform()
	{
		return m_Transform;
	}
private:
	SDL_FRect m_Transform;
	SDL_Color m_Color;
};

