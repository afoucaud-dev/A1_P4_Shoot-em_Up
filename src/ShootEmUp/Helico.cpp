#include "Helico.h"
#include "SDL.h"

Helico::Helico(int width, int height, float precision) : Ennemy(width, height, precision)
{
    m_speedennemy = width / 8.f;
}

int Helico::GetSpeed()
{
    return m_speedennemy;
}


int Helico::IsAlive() const
{
    return pv;
}

void Helico::shot(int puissance)
{
    pv -= puissance;
}



bool Helico::ManageHelico(float deltaTime, std::vector<Helico>* allhelico, int i)
{
    BasiqueMove(0.f, GetSpeed() * deltaTime);
    if (GetPosition(0.f, 1.f).y > HEIGHT + GetRadius() * 2 || IsAlive() == 0)
    {
        allhelico->erase(allhelico->begin() + i);
        return 1;
    }

    return 0;
}
