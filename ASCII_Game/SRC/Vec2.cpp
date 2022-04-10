#include "Vec2.h"

Vec2::Vec2(float x, float y) : x(x), y(y)
{		}

Vec2::Vec2(float a) : x(a), y(a)
{		}

Vec2::Vec2() : x(0), y(0)
{		}

float Vec2::Distance(Vec2 & other)
{
	return (sqrt(pow(x - other.x, 2) + pow(y - other.y, 2)));
}