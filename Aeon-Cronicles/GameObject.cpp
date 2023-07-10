#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(float x, float y, float w, float h, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	: m_Transform{ x , y , w , h }
	, m_Color{ r, g, b, a }
{

}
void GameObject::Draw(SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	SDL_RenderFillRectF(pRenderer, &m_Transform);
}

float GameObject::UpdatePositionX(float x)
{
	float X = m_Transform.x;
	X += x;
	m_Transform.x = X;
	return m_Transform.x;
}
float GameObject::UpdatePositionY(float y)
{
	float Y = m_Transform.y;
	Y += y;
	m_Transform.y = Y;
	return m_Transform.y;
}

float GameObject::GetObjectWidth()
{
	return m_Transform.w;
}

float GameObject::GetObjectHeight()
{
	return m_Transform.h;
}