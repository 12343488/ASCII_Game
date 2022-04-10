#pragma once

#include <cmath>

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
		return Vec2(x + other.x, y + other.y);
	}

	Vec2 operator- (Vec2& other)
	{
		return Vec2(x - other.x, y - other.y);
	}

	bool operator== (const Vec2& other) const
	{
		return (x == other.x && y == other.y);
	}

	float Distance(Vec2& other);
};


namespace std
{
	template<>
	struct hash <Vec2>
	{
		size_t operator()(const Vec2& key) const
		{
			return (hash<float>()(key.x) ^ (hash<float>()(key.y) << 1));
		}
	};
}