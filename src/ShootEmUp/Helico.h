#pragma once
#include "Ennemy.h"
class Helico : public Ennemy
{
private:
    float m_speedennemy;
    int pv = 1;
public:


    Helico(int width = WIDTH, int Height = HEIGHT, float precision = DEFAULT_PRECISION);

    int GetSpeed() override;

    int IsAlive() const;

    void shot(int puissance);

    bool ManageHelico(float deltaTime, std::vector<Helico>* allcar, int i);
};