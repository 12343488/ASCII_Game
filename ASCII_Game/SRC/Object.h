#pragma once

#include <list> 

#include "Vec2.h"
#include "Screen.h"
#include "PathFindig.h"

struct Object
{
	enum class Type
	{
		OBJECT = 0,
		SELFMOVABLE
	};

	Tile::GraficsID ID;
	Vec2 Coord;
	Screen* screen;
	Type type = Type::OBJECT;

	Object(Tile::GraficsID ID, Vec2 Coord, Screen& screen);
	Object(Tile::GraficsID ID, Vec2 Coord);

	void Move(Vec2 Direction);
	void Teleport(Vec2 Destination);
};

struct SelfMovableObject : public Object
{
	std::list<TileExplored> Path;

	int CouldntMove;

	SelfMovableObject(Tile::GraficsID ID, Vec2 Coord, Screen& screen);

	void ShowPath();
	void Move();
};