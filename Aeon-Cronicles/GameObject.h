#pragma once
#include <SDL.h>

enum AnimState { STATE_IDLING, STATE_RUNNING, STATE_JUMPING };

class GameObject
{
public:
	GameObject(float x, float y, float w, float h, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255);

	void Draw(SDL_Renderer* pRenderer);
	//SDL_FRect* GetTransform();//void UpdatePositionX(float x);
	SDL_FPoint GetCenter() const;
	
	void UpdatePositionX(float x);
	void UpdatePositionY(float y);

	SDL_FRect* GetTransform();
	virtual void Update() = 0;
	virtual void Render() = 0;
	const bool GetEnabled() const;
	void SetEnabled(const bool e);
protected:
	SDL_FRect m_transform;
	SDL_Color m_Color;
	bool m_enabled;
	GameObject();
	GameObject(const SDL_FRect transform);
};
class Sprite : public GameObject
{
public:
	SDL_Rect* GetSrc();
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	SDL_Rect m_src;
	Sprite(const SDL_Rect src, const SDL_FRect transform);
};
class AnimatedSprite : public Sprite
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	unsigned short m_frame, m_frameMax, m_sprite, m_spriteMin, m_spriteMax;
	AnimState m_state;
	AnimatedSprite(const SDL_Rect src, const SDL_FRect transform, AnimState state);
	void SetAnimation(AnimState state, const unsigned short frameMax, const unsigned short spriteMin,
		const unsigned short spriteMax, const int srcY = 0);
	void Animate();
};

