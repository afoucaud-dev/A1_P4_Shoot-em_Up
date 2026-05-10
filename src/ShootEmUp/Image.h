#pragma once

#include "Geometry.h"

struct SDL_Texture;

class Image : public Geometry
{
	SDL_Texture* m_texture;

public:
	Image(SDL_Renderer* renderer, const char* path);

	void Resize(int width, int height) override;

	void Draw(SDL_Renderer* renderer) override;

};

