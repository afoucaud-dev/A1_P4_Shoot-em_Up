#pragma once
#include "Character.h"

class Hero : public Character
{
private:
    float m_speedhero;
    int pv = 10;

public:

    Hero(int width = WIDTH, int Height = HEIGHT, float precision = DEFAULT_PRECISION);

    void Move(float x, float y, int W, int H);

    int GetSpeed() override;

    void Draw(SDL_Renderer* renderer) override;

    int IsAlive() const;

    void shot(int puissance);
};