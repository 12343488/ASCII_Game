#include "Object.h"

Object::Object(Tile::GraficsID ID, Vec2 Coord, Screen& screen) : ID(ID), Coord(Coord), screen(&screen)
{	
	screen.screen[Coord.x][Coord.y].Occupant = this;

	Objects.push_back(this);
}

Object::Object(Tile::GraficsID ID, Vec2 Coord) : ID(ID), Coord(Coord), screen(NULL)
{		}

void Object::Move(Vec2 Direction)
{
	if (screen)
	{
		Vec2 Destination;

		if (Direction.x > 0)
		{
			Destination = screen->screen[Coord.x][Coord.y].ReachableNeighbours[0];
		}

		if (Direction.y > 0)
		{
			Destination = screen->screen[Coord.x][Coord.y].ReachableNeighbours[1];
		}

		if (Direction.x < 0)
		{
			Destination = screen->screen[Coord.x][Coord.y].ReachableNeighbours[2];
		}

		if (Direction.y < 0)
		{
			Destination = screen->screen[Coord.x][Coord.y].ReachableNeighbours[3];
		}

		if (((Object*)screen->screen[Destination.x][Destination.y].Occupant)->ID == Tile::GraficsID::EMPTY)
		{
			(Object*)screen->screen[Coord.x][Coord.y].Occupant)->ID = Tile::GraficsID::EMPTY;

			Coord = Destination;

			screen->screen[Coord.x][Coord.y].Occupant = this;
		}
	}
}

void Object::Teleport(Vec2 Destination)
{
#ifdef _DEBUG
	if (screen)
	{
		if (((Object*)screen->screen[Destination.x][Destination.y].Occupant)->ID == Tile::GraficsID::EMPTY)
		{
			screen->screen[Coord.x][Coord.y].Occupant = new Object(Tile::GraficsID::EMPTY, Coord);

			Coord = Destination;

			((Object*)screen->screen[Coord.x][Coord.y].Occupant)->~Object();

			screen->screen[Coord.x][Coord.y].Occupant = this;
		}
	}
#endif // _DEBUG
}

