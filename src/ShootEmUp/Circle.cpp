#include "Circle.h"

#include "SDL.h"
#include "SDL_image.h"

Circle::Circle(int radius, int precision) : Geometry(radius * 2, radius * 2)
{
	m_precision = precision;
}

void Circle::Draw(SDL_Renderer* renderer)
{
	/*SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);*/

	float perimeter = 2 * M_PI;
	float step = perimeter / m_precision;

	float radius = GetRadius();

	Vector2f center = GetPosition(0.5f, 0.5f);

	int lastX = radius * cos(0) + center.x;
	int lastY = radius * sin(0) + center.y;

	for (int i = 1; i <= m_precision; i++)
	{
		int currentX = radius * cos(step * i) + center.x;
		int currentY = radius * sin(step * i) + center.y;

		SDL_RenderDrawLine(renderer, lastX, lastY, currentX, currentY);

		lastX = currentX;
		lastY = currentY;
	}
}

bool Circle::IsColliding(const Circle* target)
{
	Vector2f center1 = GetPosition(0.5f, 0.5f);
	Vector2f center2 = target->GetPosition(0.5f, 0.5f);

	float distance = Math::GetDistance(center1.x, center1.y, center2.x, center2.y);
	float radiusDist = GetRadius() + target->GetRadius();

	return distance <= radiusDist;
}
