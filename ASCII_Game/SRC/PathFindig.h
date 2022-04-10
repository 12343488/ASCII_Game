#pragma once

#include <unordered_map>
#include <vector>
#include <list>
#include <iostream>

#include "Vec2.h"
#include "Screen.h"

struct TileExplored
{
	int steps;
	float modifier, distance;

	Vec2 Coord, Parent;

	TileExplored(Vec2 Coord, Vec2 Parent, int steps, float modifier, float distance);

	float Coast();
};

void AstarPathFinding(Vec2 Target, void* Searcher, Screen& screen, int show);