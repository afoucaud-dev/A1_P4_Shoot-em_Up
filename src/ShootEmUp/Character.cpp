#include "Character.h"
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

Character::Character(int radius, int precision, int width, int height) : Geometry(radius * 2, radius * 2)
{
    m_precision = precision;
}

void Character::Draw(SDL_Renderer* renderer)
{

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

bool Character::IsColliding(const Character* target)
{
    Vector2f center1 = GetPosition(0.5f, 0.5f);
    Vector2f center2 = target->GetPosition(0.5f, 0.5f);

    float distance = Math::GetDistance(center1.x, center1.y, center2.x, center2.y);
    float radiusDist = GetRadius() + target->GetRadius();

    return distance <= radiusDist;
}

int Character::GetSpeed() {
    return 0;
}




int Character::Proximity(Character* target)
{
    int hero_x = target->GetPosition().x;
    int hero_y = target->GetPosition().y;
    int ennemy_x = GetPosition().x;
    int ennemy_y = GetPosition().y;

    int size_x = abs(hero_x - ennemy_x);
    int size_y = abs(hero_y - ennemy_y);

    int proximity = size_x + size_y;


    return proximity;
}


void Character::NewTarget(int dist)
{
    m_target = dist;
}


int Character::Target()
{
    return m_target;
}