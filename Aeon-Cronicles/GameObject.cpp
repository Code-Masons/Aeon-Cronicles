#include "GameObject.h"

GameObject::GameObject(float x, float y, float w, float h, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	: m_transform{ x , y , w , h }
	, m_Color{ r, g, b, a }, m_enabled(true) 
{

}
void GameObject::Draw(SDL_Renderer* pRenderer)
{

	SDL_SetRenderDrawColor(pRenderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	SDL_RenderFillRectF(pRenderer, &m_transform);
}
SDL_FRect* GameObject::GetTransform()
{
	return &m_transform;
}
SDL_FPoint GameObject::GetCenter() const
{
	return { m_transform.x + m_transform.w / 2, m_transform.y + m_transform.h / 2 };
}
const bool GameObject::GetEnabled() const
{
	return m_enabled;
}
void GameObject::SetEnabled(const bool e)
{
	m_enabled = e;
}
Sprite::Sprite(const SDL_Rect src, const SDL_FRect transform)
	:GameObject(transform), m_src(src) {}

SDL_Rect* Sprite::GetSrc()
{
	return &m_src;
}
void AnimatedSprite::SetAnimation(AnimState state, const unsigned short frameMax, const unsigned short spriteMin,
	const unsigned short spriteMax, const int srcY)
{
	m_state = state;
	m_frame = 0;
	m_frameMax = frameMax;
	m_sprite = m_spriteMin = spriteMin;
	m_spriteMax = spriteMax;
	m_src.x = m_src.w * m_sprite;
	m_src.y = srcY;
}
void AnimatedSprite::Animate()
{
	if (m_frame++ == m_frameMax)
	{
		m_frame = 0;
		if (++m_sprite == m_spriteMax)
			m_sprite = m_spriteMin; // I don't use % in case m_sprite doesn't start at 0.
		m_src.x = m_src.w * m_sprite; // Moved to outside if.
	}
}


void GameObject::UpdatePositionX(float x)
{
	m_transform.x += x;
}
void GameObject::UpdatePositionY(float y)
{
	m_transform.y += y;
}

////Men