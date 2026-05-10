#include "TankBoss.h"
#include "SDL.h"

TankBoss::TankBoss(int width, int height, float precision) : Character(width / 15, width, height, precision)
{
    m_speedtank = width / 1.7;
}

int TankBoss::GetSpeed()
{
    return m_speedtank;
}


int TankBoss::IsAlive() const
{
    return pv;
}

void TankBoss::shot(int puissance)
{
    pv -= puissance;
}

bool direction = false;
int count = 0;
int turnpattern = 0;

int TankBoss::Manage1Boss(float deltaTime, std::vector<TankBoss>* allboss, int i)
{
    if (!direction)
    {
        BasiqueMove(GetSpeed() * deltaTime, 0.f);
    }

    if (direction)
    {
        BasiqueMove(-GetSpeed() * deltaTime, 0.f);
    }

    if (GetPosition(0.f, 1.f).x > WIDTH - GetRadius() * 2)
    {
        direction = true;
        turnpattern++;
    }

    if (GetPosition(0.f, 1.f).x < 0)
    {
        direction = false;
    }

    if (IsAlive() == 0)
    {
        allboss->erase(allboss->begin() + i);
        return 1;
    }

    if (turnpattern == pattern1)
    {
        turnpattern = 0;
        return 2;
    }

    return 0;
}


bool back = false;

int TankBoss::Manage2Boss(float deltaTime, std::vector<TankBoss>* allboss, int i, Hero* hero)
{
    int hero_x = hero->GetPosition().x;

    if (count >= 100)
    {
        if (!back)
        {
            BasiqueMove(0.f, GetSpeed() * 2 * deltaTime);
        }

        if (GetPosition().y >= HEIGHT || back)
        {
            BasiqueMove(0.f, -GetSpeed() * deltaTime);
            back = true;
            if (GetPosition().y <= 0)
            {
                back = false;
                count = 0;
                turnpattern++;
            }
        }
    }

    else if (hero_x > GetPosition().x)
    {
        BasiqueMove(GetSpeed() * deltaTime, 0.f);
        count++;
    }

    else if (hero_x < GetPosition().x)
    {
        BasiqueMove(-GetSpeed() * deltaTime, 0.f);
        count++;
    }

    if (IsColliding(hero) && !back)
    {
        hero->shot(2);
        back = true;
    }

    if (IsAlive() == 0)
    {
        allboss->erase(allboss->begin() + i);
        return 1;
    }

    if (turnpattern == pattern2)
    {
        turnpattern = 0;
        return 2;
    }

    return 0;
}