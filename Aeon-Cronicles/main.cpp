#include <iostream>
#include <SDL.h>
#include <chrono>
#include "Game.h"
#include "states.h"
#include "stateManager.h"

struct vec2
{
	float x = 0;
	float y = 0;
};

struct Sprite
{
private:

	SDL_Texture* pTexture;
	SDL_Rect src;
	SDL_Rect Dst;
	//these are public fields.variable which compose our new type Sprite.
	//public means that things outside this struct or class can access them.
public:
	int animationframecount = 1;
	float animationcurrentframe = 0;
	vec2 position;
	double rotation = 0.0;
	SDL_RendererFlip flipstate = SDL_FLIP_NONE;

	//constructors are special member fuctions of a class or struct which are used to intialize or change them
	//the compiler knows a construcor by the fact that it has the same name as the class and does not have a return type
	//the constructore with no arguments is called default constructor
	Sprite()
	{
		std::cout << "Sprite default constructor!" << std::endl;
		pTexture = nullptr;
		src = { 0,0,0,0 };
		Dst = { 0,0,0,0 };
	}

	//Sprite(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color) : Sprite()
	//{
	//	SDL_Surface* pSurf = TTF_RenderText_Solid(font, text, color);
	//	pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurf);
	//	SDL_FreeSurface(pSurf); //Free memory associated with surface, it was used just to make a texture.
	//	TTF_SizeText(font, text, &src.w, &src.h);
	//	Dst.w = src.w;
	//	Dst.h = src.h;
	//}

	// A non-default constructor can take arguments
	Sprite(SDL_Renderer* renderer, const char* imagefilepath)
	{
		std::cout << "Sprite default constructor!" << std::endl;
		pTexture = IMG_LoadTexture(renderer, imagefilepath);
		if (pTexture == NULL)
		{
			std::cout << "Image load failed!" << SDL_GetError() << std::endl;
		}
		else
		{
			std::cout << "Image load successful!\n";
		}

		//query for our texture's width and height to set a default source rect value spanning the whole texture
		if (SDL_QueryTexture(pTexture, NULL, NULL, &src.w, &src.h) != 0) {
			std::cout << "Query Texture failed!" << SDL_GetError() << std::endl;
		}
		//at this poinyt,SDL_QueryTexture has presumably used the addresses for src.w and h to place the width and height into that memory
		src.x = 0;
		src.y = 0;

		Dst.x = 0;
		Dst.y = 0;
		Dst.w = src.w;
		Dst.h = src.h;
	}
	Sprite(SDL_Renderer* renderer, const char* imagefilepath, int framewidth, int frameheight, int numberofframesinsheet) :Sprite(renderer, imagefilepath)
	{
		src.w = framewidth;
		src.h = frameheight;
		Dst.w = framewidth;
		Dst.h = frameheight;
		animationframecount = numberofframesinsheet;
	}

	// we can also declare member functions which are 'called on' instnces of this struct or class
	void Draw(SDL_Renderer* renderer)
	{
		Dst.x = position.x;
		Dst.y = position.y;
		src.x = (int)animationcurrentframe * src.w;
		int result = SDL_RenderCopy(renderer, pTexture, &src, &Dst);
		if (result != 0) {
			std::cout << "Render failed!" << SDL_GetError() << std::endl;
		}
	}
	void setanimationframedimensions(int framewidth, int frameheight)
	{
		src.w = framewidth;
		src.h = frameheight;
	}
	void NextFrame()
	{
		addframetime(1.0f);

	}
	void addframetime(float frames)
	{
		animationcurrentframe += frames;
		if (animationcurrentframe >= animationframecount)
		{
			animationcurrentframe = 0;
		}
	}
	void SetPosition(int x, int y)
	{
		position.x = x;
		position.y = y;
	}
	void setsize(int x, int y)
	{
		Dst.w = x;
		Dst.h = y;
	}
	SDL_Rect GetRect() const//const keyword says "this function does not anythig about class"
	{
		SDL_Rect returnvalue = Dst;
		returnvalue.x = position.x;
		returnvalue.y = position.y;
		return Dst;
	}
	vec2 Getsize() const
	{
		vec2 sizeXY = { Dst.w,Dst.h };
		return sizeXY;
	}
	void CleanUp()
	{
		SDL_DestroyTexture(pTexture);
	}

};
int main(int argc, char* argv[])
{
	Game& myGameInstance = Game::GetInstance();
	int result = myGameInstance.Init("GAME1017", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	if (result == 0)
	{
		auto lastFrameTime = std::chrono::high_resolution_clock::now();
		while (myGameInstance.IsRunning())
		{
			auto thisFrameTime = std::chrono::high_resolution_clock::now();

			std::chrono::duration<float> lastFrameDurration = thisFrameTime - lastFrameTime;

			float deltaTime = lastFrameDurration.count();

			lastFrameTime = thisFrameTime;

			myGameInstance.HandleEvents();
			myGameInstance.Update(deltaTime);
			myGameInstance.Render();

		}
		myGameInstance.Clean();
	}

	return result;
}