#pragma once

#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <iomanip>
#include <deque>

#include "Vec2.h"

struct Tile
{
	enum class GraficsID
	{
		EMPTY = 0,
		PLAYER,
		WALL
	};

	Vec2 Coord;

	std::array<Vec2, 4> ReachableNeighbours;

	/*
		Vec2(Coord.x + 1.0f	, Coord.y		),	>
		Vec2(Coord.x		, Coord.y + 1.0f),	^
		Vec2(Coord.x - 1.0f	, Coord.y		),	<
		Vec2(Coord.x		, Coord.y - 1.0f)	B
	*/

	void* Occupant;

	//basicamente não vai se usar esses construtores no meio do jogo
	Tile(Vec2& Coord, std::array<Vec2, 4>& Reachable);
	Tile(Vec2& Coord, Vec2& Limits);
};

const std::string Grafics(Tile::GraficsID ID);

struct Screen
{
	//[x, y]
	std::vector<std::vector<Tile>> screen;

	std::deque<void*> Objects;

	Vec2 Limits;
	int ScreenHeight = 10; //screen height é o tanto de linhas puladas a cada "frame"

	Screen(int X, int Y);

	void Display();
};