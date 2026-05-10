#include "Car.h"
#include "SDL.h"

Car::Car(int width, int height, float precision) : Ennemy(width, height, precision)
{
    m_speedennemy = width / 6.f;
}

int Car::GetSpeed()
{
    return m_speedennemy;
}

int Car::IsAlive() const
{
    return pv;
}

void Car::shot(int puissance)
{
    pv -= puissance;
}



bool Car::ManageCar(float deltaTime, std::vector<Car>* allcar, int i, int* score)
{
    BasiqueMove(0.f, GetSpeed() * deltaTime);
    if (GetPosition(0.f, 1.f).y > HEIGHT + GetRadius() * 2 || IsAlive() == 0)
    {
        allcar->erase(allcar->begin() + i);
        if (IsAlive() == 0)
        {
            *score += 10;
        }
        return 1;
    }

    return 0;
}
