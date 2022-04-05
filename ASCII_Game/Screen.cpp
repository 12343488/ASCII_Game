#include "Screen.h"
#include "Object.h"

Tile::Tile(Vec2& Coord, std::array<Vec2, 4>& Reachable) : Coord(Coord), Occupant(new Object(Tile::GraficsID::EMPTY, Coord))
{	
	ReachableNeighbours = Reachable;
}

Tile::Tile(Vec2& Coord, Vec2& Limits) : Coord(Coord), Occupant(new Object(Tile::GraficsID::EMPTY, Coord))
{
	ReachableNeighbours = {
			Vec2(Coord.x + 1.0f	 , Coord.y),
			Vec2(Coord.x		 , Coord.y + 1.0f),
			Vec2(Coord.x - 1.0f	 , Coord.y),
			Vec2(Coord.x		 , Coord.y - 1.0f)
	};

	if (Coord.x == Limits.x - 1.0f)
	{
		ReachableNeighbours[0] = Vec2(0.0f	 , Coord.y		  ); 
	}

	if (Coord.y == Limits.y - 1.0f)
	{
		ReachableNeighbours[1] = Vec2(Coord.x, 0.0f			  );
	}

	if (Coord.x == 0)
	{
		ReachableNeighbours[2] = Vec2(Limits.x - 1.0f, Coord.y);
	}

	if (Coord.y == 0)
	{
		ReachableNeighbours[3] = Vec2(Coord.x, Limits.y - 1.0f);
	}
}

Screen::Screen(int X, int Y) : Limits(Vec2(X, Y))
{
	for (int x = 0; x < Limits.x; x++)
	{
		std::vector<Tile> TempVec;

		for (int y = 0; y < Limits.y; y++)
		{
			Vec2 CoordsInit(x, y);
			
			TempVec.push_back(Tile(CoordsInit, Limits));
		}

		screen.push_back(TempVec);
	}
}

void Screen::Display()
{
	for (int i = 0; i < ScreenHeight; i++)
	{
		std::cout << "\n";
	}

	for (int y = Limits.y - 1; y >= 0; y--)
	{
		for (int x = 0; x < Limits.x; x++)
		{
			std::cout << std::setw(4) << Grafics(((Object*)screen[x][y].Occupant)->ID);
		}

		std::cout << "\n";
	}
}

const std::string Grafics(Tile::GraficsID ID)
{
	switch (ID)
	{
	case Tile::GraficsID::EMPTY:
		return " + ";
		break;
	case Tile::GraficsID::PLAYER:
		return " O ";
		break;
	case Tile::GraficsID::WALL:
		return "|#|";
		break;
	}

	return " * ";
}
