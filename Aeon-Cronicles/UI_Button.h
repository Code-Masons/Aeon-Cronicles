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
