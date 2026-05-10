#include "Obstacle.h"
#include "SDL_image.h"
#include "SDL.h"

Obstacle::Obstacle(int width, int height, float precision) : Character(width / 25, width, height, precision)
{
    m_speedobstacle = width / 2.f;
}

void Obstacle::Draw(SDL_Renderer* renderer)
{
    Character::Draw(renderer);
}

int Obstacle::GetSpeed()
{
    return m_speedobstacle;
}


int Obstacle::IsAlive() const
{
    return pv;
}

void Obstacle::shot(int puissance)
{
    pv -= puissance;
}


bool Obstacle::ManageObstacle(float deltaTime, std::vector<Obstacle>* allobstacle, int i, Hero hero, int* score)
{
    int speed = GetSpeed() * deltaTime;
    BasiqueMove(0.f, GetSpeed() * deltaTime);

    if (GetPosition(0.f, 1.f).y > HEIGHT + GetRadius() * 2 || IsAlive() == false)
    {
        allobstacle->erase(allobstacle->begin() + i);
        return 1;
    }

    if (IsColliding(&hero))
    {
        shot(4);
        if (IsAlive() == 0)
        {
            allobstacle->erase(allobstacle->begin() + i);
			*score -= 10;
            return 1;
        }
    }
    return 0;
}
