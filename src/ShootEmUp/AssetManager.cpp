#include "AssetManager.h"

#include <iostream>
#include <SDL_image.h>
#include <SDL.h>

AssetManager* AssetManager::Instance = nullptr;

AssetManager* AssetManager::Get()
{
	if (Instance == nullptr)
		Instance = new AssetManager();

	return Instance;
}

SDL_Texture* AssetManager::LoadTexture(SDL_Renderer* renderer, const char* path)
{
	auto it = m_textures.find(path);
	if (it != m_textures.end())
		return it->second;

	SDL_Surface* surface = IMG_Load(path);
	if (!surface)
	{
		std::cout << "IMG_Load error (" << path << ") : "
			<< IMG_GetError() << std::endl;
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!texture)
	{
		std::cout << "CreateTexture error: "
			<< SDL_GetError() << std::endl;
		return nullptr;
	}

	m_textures[path] = texture;
	return texture;
}