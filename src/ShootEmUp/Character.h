#pragma once
#include <vector>
#include "Geometry.h"

#define DEFAULT_PRECISION 30
#define WIDTH 1245
#define HEIGHT 700
#define CENTER_X (WIDTH - 1) / 2
#define CENTER_Y (HEIGHT - 1) / 2
#define TARGET_FPS 60
#define TARGET_DELTA_TIME 1.f / TARGET_FPS

class Character : public Geometry
{
	int m_precision;
	int m_target = -1;

public:
	Character(int radius, int precision = DEFAULT_PRECISION, int width = WIDTH, int height = HEIGHT);

	void Draw(SDL_Renderer* renderer) override;

	int GetRadius() const { return m_width / 2; }

	virtual int GetSpeed();

	bool IsColliding(const Character* target);

	int Proximity(Character* target);

	void NewTarget(int dist);

	int Target();
};

