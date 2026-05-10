#include "Image.h"

#include "SDL.h"
#include "SDL_image.h"

#include <iostream>
#include "AssetManager.h"

Image::Image(SDL_Renderer* renderer, const char* path) : Geometry(-1, -1)
{
	m_texture = AssetManager::Get()->LoadTexture(renderer, path);

	SDL_QueryTexture(m_texture, NULL, NULL, &m_width, &m_height);
}

void Image::Resize(int width, int height)
{
	float factorWidth = width / m_width;
	float factorHeight = height / m_height;

	float factorMin = std::min(factorWidth, factorHeight);

	m_width *= factorMin;
	m_height *= factorMin;
}

void Image::Draw(SDL_Renderer* renderer)
{
	SDL_Rect dst = { m_x, m_y, m_width, m_height };

	SDL_RenderCopy(renderer, m_texture, NULL, &dst);
}
