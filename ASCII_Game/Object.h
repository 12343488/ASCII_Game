#pragma once

#include <deque> 

#include "Vec2.h"
#include "Screen.h"

struct Object
{
	Tile::GraficsID ID;
	Vec2 Coord;
	Screen* screen;

	Object(Tile::GraficsID ID, Vec2 Coord, Screen& screen);
	Object(Tile::GraficsID ID, Vec2 Coord);

	void Move(Vec2 Direction);
	void Teleport(Vec2 Destination);
};