#include "Hero.h"
#include "SDL.h"

Hero::Hero(int width, int height, float precision) : Character(width / 25, width, height, precision)
{
    m_speedhero = width / 1.5f;
}

int Hero::GetSpeed()
{
    return m_speedhero;
}


void Hero::Move(float x, float y, int W, int H)
{
    MoveHero(x, y, W, H);
}

void Hero::Draw(SDL_Renderer* renderer)
{
    Character::Draw(renderer);
}

int Hero::IsAlive() const
{
    return pv;
}

void Hero::shot(int puissance)
{
    pv -= puissance;
}