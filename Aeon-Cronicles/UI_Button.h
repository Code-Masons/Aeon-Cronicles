//#pragma once
//#include "GameObject.h"
//#include "sprite.h"
//#include <string>
//#include "SDL.h"
//class Ui_Button : public Sprite
//{
//public:
//	Ui_Button(SDL_Rect source, SDL_FRect destination, const char* characterKey);
//	virtual void Update(float DeltaTime) override;
//	virtual void Render()override;
//
//protected:
//	std::string m_textureKey;
//
//	enum class ButtonState
//	{
//		STATE_UP,
//		STATE_OVER,
//		STATE_DOWN
//	};
//
//	ButtonState m_state;
//
//	virtual void Execute() = 0;
//};
//

#pragma once
#include "GameObject.h"
#include <string>

class UIButton : public GameObject
{
public:
    UIButton(float x, float y, float w, float h);

    bool CheckIsHovered() { return m_IsHovered; }
    void HandleEvent();

private:
    SDL_Texture* m_Texture;
    bool m_IsHovered;
};