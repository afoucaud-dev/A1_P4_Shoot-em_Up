#pragma once
#include "Ennemy.h"
class Moto : public Ennemy
{
private:
    float m_speedennemy;
    int pv = 2;
public:


    Moto(int width = WIDTH, int Height = HEIGHT, float precision = DEFAULT_PRECISION);

    int GetSpeed() override;

    int IsAlive() const;

    void shot(int puissance);

    bool ManageMoto(float deltaTime, std::vector<Moto>* allcar, int i, int*score);
};