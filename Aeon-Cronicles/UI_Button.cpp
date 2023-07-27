//#include "Ui_Button.h"
//#include "Game.h"
//#include "TextureManager.h"
//#include "EventManager.h"
//
//Ui_Button::Ui_Button(SDL_Rect source, SDL_FRect destination, const char* textureKey)
//	:Sprite(source,destination)
//	, m_textureKey(textureKey)
//	, m_state(ButtonState::STATE_UP)
//{
//
//}
//
//void Ui_Button::Render()
//{
//	m_sourceTransform.x = m_sourceTransform.w * (int)m_state;
//	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture(m_textureKey), &m_sourceTransform, &m_destinationTransform);
//}
//
//void Ui_Button::Update(float deltaTime)
//{
//	SDL_Rect intDestinationRect = { (int)m_destinationTransform.x, (int)m_destinationTransform.y, (int)m_destinationTransform.w, (int)m_destinationTransform.h };
//	bool mouseOverlap = SDL_PointInRect(&EventManager::GetMousePos(), &intDestinationRect);
//	switch (m_state)
//	{
//	case ButtonState::STATE_UP:
//		if (mouseOverlap)
//		{
//			m_state = ButtonState::STATE_OVER;
//			EventManager::SetCursor(SDL_SYSTEM_CURSOR_HAND);
//		}
//		break;
//	case ButtonState::STATE_OVER:
//		if (!mouseOverlap)
//		{
//			m_state = ButtonState::STATE_UP;
//			EventManager::SetCursor(SDL_SYSTEM_CURSOR_ARROW);
//		}
//		else if (mouseOverlap && EventManager::MousePressed(1))
//		{
//			m_state = ButtonState::STATE_DOWN; // 1 is for left mouse
//
//		}
//		break;
//	case ButtonState::STATE_DOWN:
//		if (mouseOverlap)//left mouse released
//		{
//			m_state = ButtonState::STATE_OVER;
//			Execute();
//		}
//		else
//		{
//			m_state = ButtonState::STATE_UP;
//			EventManager::SetCursor(SDL_SYSTEM_CURSOR_ARROW);
//		}
//		break;
//	}
//}

#include "UI_Button.h"
#include <SDL_image.h>
#include <iostream>
#include "Game.h"

UIButton::UIButton(float x, float y, float w, float h, const std::string& imagePath)
    : GameObject(x, y, w, h)
    , m_Texture(nullptr)
    , m_IsHovered(false)
    , m_IsClicked(false)
{
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (!surface)
    {
        std::cerr << "Failed to load image: " << imagePath << ". Error: " << IMG_GetError() << std::endl;
        return;
    }

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void UIButton::HandleEvent(const SDL_Event& event)
{
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        bool isInside = mouseX >= static_cast<int>(GetTransform().x) && mouseX <= static_cast<int>(GetTransform().x + GetTransform().w)
            && mouseY >= static_cast<int>(GetTransform().y) && mouseY <= static_cast<int>(GetTransform().y + GetTransform().h);

        if (isInside)
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                m_IsClicked = true;
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                m_IsClicked = false;
            }

            m_IsHovered = true;
        }
        else
        {
            m_IsHovered = false;
            m_IsClicked = false;
        }
    }
}

void UIButton::Render(SDL_Renderer* pRenderer)
{
    if (m_IsClicked)
    {
        SDL_SetTextureColorMod(m_Texture, 100, 100, 100); // Darken the button when clicked
    }
    else if (m_IsHovered)
    {
        SDL_SetTextureColorMod(m_Texture, 255, 255, 255); // Reset the color modulation when hovered
    }
    else
    {
        SDL_SetTextureColorMod(m_Texture, 200, 200, 200); // Apply a slight color modulation when not hovered
    }

    SDL_RenderCopyF(pRenderer, m_Texture, nullptr, &GetTransform());
}