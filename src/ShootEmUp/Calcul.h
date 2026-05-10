#pragma once

struct Vector2
{
	int x;
	int y;
};

struct Vector2f
{
	float x;
	float y;
};

namespace Math
{
	float GetDistance(float x1, float y1, float x2, float y2);
}