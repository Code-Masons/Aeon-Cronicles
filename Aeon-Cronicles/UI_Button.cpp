#include "UI_Button.h"
#include <SDL_image.h>
#include <iostream>
#include "Game.h"
#include "EventManager.h"
#include "MathManager.h"

UIButton::UIButton(float x, float y, float w, float h)
    : GameObject(x, y, w, h)
    , m_IsHovered(false)
{}

void UIButton::HandleEvent()
{
    SDL_Point mousePos = EventManager::GetMousePos(); // Use GetMousePos function from EventManager
    SDL_Rect button = MathManager::ConvertFRect2Rect(GetTransform());
    bool isInside = SDL_PointInRect(&mousePos, &button);

    m_IsHovered = isInside;
}
