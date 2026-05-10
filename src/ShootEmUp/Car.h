#pragma once
#include "Ennemy.h"
class Car : public Ennemy
{
private:
    float m_speedennemy;
    int pv = 2;
public:


    Car(int width = WIDTH, int Height = HEIGHT, float precision = DEFAULT_PRECISION);

    int GetSpeed() override;

    int IsAlive() const;

    void shot(int puissance);

    bool ManageCar(float deltaTime, std::vector<Car>* allcar, int i, int* score);
};