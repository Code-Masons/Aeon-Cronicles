#pragma once
#include <SDL.h>
class Game
{
public:
	static const int kWidth = 1024;
	static const int kHeight = 769;
	static Game& GetInstance();

	int Init(const char* title, int Xpos, int Ypos);
	bool IsRunning();
	bool KeyDown(SDL_Scancode key);
	bool KeyReleased(SDL_Scancode key);
	void HandleEvents();
	void Quit();
	void Update(float deltaTime);
	void Render();
	void Clean();

	SDL_Window* GetWindow() { return m_pWindow; }
	SDL_Renderer* GetRenderer() { return m_pRenderer; }

private:
	Game();
	bool m_running;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	SDL_FRect m_RectangleTransform;
	const Uint8* m_keyStates;
};

