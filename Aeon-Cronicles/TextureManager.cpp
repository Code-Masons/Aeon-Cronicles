#include "TextureManager.h"
#include "Game.h"
#include <iostream>

std::map<std::string, SDL_Texture*> TextureManager::s_textures;

SDL_Texture* TextureManager::Load(const char* path, const std::string key)
{
	SDL_Texture* temp = IMG_LoadTexture(Game::GetInstance().GetRenderer(), path);

	if (temp == nullptr)
	{
		std::cout << "could not load texture. ERROR: " << IMG_GetError() << std::endl;
	}

	else
	{
		s_textures.emplace(key, temp);//add to the map
		std::cout << "successfully loaded textture" << std::endl;
	}
	return temp;
}

void TextureManager::UnLoad(const std::string key)
{
	if (s_textures.find(key) != s_textures.end())
	{
		SDL_DestroyTexture(s_textures[key]);//deallocates texture 
		s_textures.erase(key);// remove texture pointer to map
	}

	else
	{
		std::cout << "could not unload " << key << " not found" << std::endl;
	}
}

SDL_Texture* TextureManager::GetTexture(const std::string key)
{
	return s_textures[key];
}

void TextureManager::Quit()
{
	for (auto const& i : s_textures)
	{
		SDL_DestroyTexture(s_textures[i.first]);
	}
	s_textures.clear();
}
