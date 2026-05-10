#pragma once
#include "Character.h"
#include "Hero.h"

class TankBoss : public Character
{
private:
    float m_speedtank;
    int pv = 20;
    int pattern1 = 1;
    int pattern2 = 3;

public:

    TankBoss(int width = WIDTH, int Height = HEIGHT, float precision = DEFAULT_PRECISION);

    int GetSpeed() override;

    int IsAlive() const;

    void shot(int puissance);

    int Manage1Boss(float deltaTime, std::vector<TankBoss>* allboss, int i);

    int Manage2Boss(float deltaTime, std::vector<TankBoss>* allboss, int i, Hero* hero);
};