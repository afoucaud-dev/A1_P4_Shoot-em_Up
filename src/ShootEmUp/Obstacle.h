#pragma once
#include "Hero.h"
#include "Character.h"

class Obstacle : public Character
{
private:
    int m_speedobstacle;
    int pv = 4;
public:
    Obstacle(int width = WIDTH, int Height = HEIGHT, float precision = DEFAULT_PRECISION);

    void Draw(SDL_Renderer* renderer) override;

    int GetSpeed() override;

    int IsAlive() const;

    void shot(int puissance);

    bool ManageObstacle(float deltaTime, std::vector<Obstacle>* allobstacle, int i, Hero hero, int* score);
};