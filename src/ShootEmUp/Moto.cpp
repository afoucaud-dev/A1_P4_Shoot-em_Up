#include "Moto.h"
#include "SDL.h"

Moto::Moto(int width, int height, float precision) : Ennemy(width, height, precision)
{
    m_speedennemy = width / 4.f;
}

int Moto::GetSpeed()
{
    return m_speedennemy;
}


int Moto::IsAlive() const
{
    return pv;
}

void Moto::shot(int puissance)
{
    pv -= puissance;
}



bool Moto::ManageMoto(float deltaTime, std::vector<Moto>* allmoto, int i, int* score)
{
    BasiqueMove(0.f, GetSpeed() * deltaTime);
    if (GetPosition(0.f, 1.f).y > HEIGHT + GetRadius() * 2 || IsAlive() == 0)
    {
        allmoto->erase(allmoto->begin() + i);
        if (IsAlive() == 0)
        {
            *score += 10;
        }
        return 1;
    }

    return 0;
}