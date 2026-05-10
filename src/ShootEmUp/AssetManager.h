#pragma once

struct SDL_Texture;
struct SDL_Renderer;

#include <map>

class AssetManager
{
	static AssetManager* Instance;

	std::map<const char*, SDL_Texture*> m_textures;

public:
	static AssetManager* Get();

	SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* path);

};

