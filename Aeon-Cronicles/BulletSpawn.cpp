#include "BulletSpawn.h"

#include "Game.h"
#include "StateManager.h"

BulletSpawn::BulletSpawn(const SDL_FRect dst, const double dx, const double dy)
	: GameObject(dst.x, dst.y, dst.w, dst.h) // Initialize the base class GameObject
	, m_dx(dx)
	, m_dy(dy)
	, m_dst(dst) // Store the destination rect for rendering
{
}

void BulletSpawn::Update()
{
	m_dst.x += (float)m_dx * s_speed * 100;
	m_dst.y += (float)m_dy * s_speed * 100;
	// Optional method of cleaning bullets.
	// if bullet goes off screen (four bounds checks)
		// flip deleteMe flag to true.
}

void BulletSpawn::Render()
{
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 240, 255, 0, 255);
	SDL_RenderFillRectF(Game::GetInstance().GetRenderer(), &m_dst);
}

const float BulletSpawn::s_speed = 300.0f;
