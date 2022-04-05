#pragma once

struct Vec2
{
	float x, y;

	Vec2(float x, float y);
	Vec2(float a);
	Vec2();

	void operator+= (Vec2& other)
	{
		x += other.x;
		y += other.y;
	}

	Vec2 operator+ (Vec2& other)
	{
		return (x + other.x, y + other.y);
	}
};