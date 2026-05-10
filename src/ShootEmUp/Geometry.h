#pragma once

#include "Calcul.h"

struct SDL_Renderer;

struct Color
{
	int r;
	int g;
	int b;
	int a;
};

class Geometry
{
protected:
	float m_x;
	float m_y;
	int m_width;
	int m_height;

	Color m_color;


public:

	Geometry(int width, int height);

	Vector2f GetPosition(float anchorX = 0.5f, float anchorY = 0.5f) const;

	virtual void SetPosition(const Vector2f& position, float anchorX = 0.5f, float anchorY = 0.5f);
	void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f);
	void MoveHero(float x, float y, int W, int H);
	void BasiqueMove(float x, float y);
	int Shot(char pos);


	void SetColor(const Color& color) { m_color = color; }

	virtual void Resize(int width, int height);

	virtual void Draw(SDL_Renderer* renderer) = 0;

	bool ContainsPoint(int px, int py) const;

};

