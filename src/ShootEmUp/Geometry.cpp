#include "Geometry.h"

Geometry::Geometry(int width, int height)
{
	m_x = 0;
	m_y = 0;
	m_width = width;
	m_height = height;

	m_color = { 255,255,255,255 };
}

Vector2f Geometry::GetPosition(float anchorX, float anchorY) const
{
	Vector2f pos;

	pos.x = m_x + m_width * anchorX;
	pos.y = m_y + m_height * anchorY;

	return pos;
}

void Geometry::SetPosition(const Vector2f& position, float anchorX, float anchorY)
{
	SetPosition(position.x, position.y, anchorX, anchorY);
}

void Geometry::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Geometry::SetPosition(float x, float y, float anchorX, float anchorY)
{
	m_x = x - m_width * anchorX;
	m_y = y - m_height * anchorY;
}

void Geometry::BasiqueMove(float x, float y)
{
	m_x += x;
	m_y += y;
}

void Geometry::MoveHero(float x, float y, int W, int H)
{
	if ((m_y > H - H / 2 || y > 0) && (m_y < H - 100 || y < 0))
	{
		m_y += y;
	}
	if ((m_x > W / 8 || x > 0) && (m_x + 100 < (W - W / 8) || x < 0))
	{
		m_x += x;
	}
}

int Geometry::Shot(char pos)
{
	if (pos == 'x')
	{
		return m_x;
	}
	else if (pos == 'y')
	{
		return m_y;
	}
}

bool Geometry::ContainsPoint(int px, int py) const
{
	float x = m_x;
	float y = m_y;

	int width = m_width;
	int height = m_height;

	if (px >= x && px <= x + width &&
		py >= y && py <= y + height)
	{
		return true;
	}

	return false;
}