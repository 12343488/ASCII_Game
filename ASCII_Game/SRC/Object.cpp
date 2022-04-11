#include "Object.h"

Object::Object(Tile::GraficsID ID, Vec2 Coord, Screen& screen) : ID(ID), Coord(Coord), screen(&screen)
{	
	screen.screen[Coord.x][Coord.y].Occupant = this;

	screen.Objects.push_back(this);
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
			Destination = screen->screen[Coord.x][Coord.y].ReachableNeighbours[0].first;
		}

		if (Direction.y > 0)
		{
			Destination = screen->screen[Coord.x][Coord.y].ReachableNeighbours[1].first;
		}

		if (Direction.x < 0)
		{
			Destination = screen->screen[Coord.x][Coord.y].ReachableNeighbours[2].first;
		}

		if (Direction.y < 0)
		{
			Destination = screen->screen[Coord.x][Coord.y].ReachableNeighbours[3].first;
		}

		if (((Object*)screen->screen[Destination.x][Destination.y].Occupant)->ID == Tile::GraficsID::EMPTY)
		{
			screen->screen[Coord.x][Coord.y].Occupant = new Object(Tile::GraficsID::EMPTY, Coord);

			Coord = Destination;

			((Object*)screen->screen[Coord.x][Coord.y].Occupant)->~Object();

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

SelfMovableObject::SelfMovableObject(Tile::GraficsID ID, Vec2 Coord, Screen& screen) : Object(ID, Coord, screen), CouldntMove(0)
{
	type = Object::Type::SELFMOVABLE;

	screen.SelfMovObjects.push_back(this);
}

void SelfMovableObject::ShowPath()
{
	for (int i = 0; i < screen->ScreenHeight; i++)
	{
		std::cout << "\n";
	}

	for (int y = screen->Limits.y - 1; y >= 0; y--)
	{
		std::vector<TileExplored> InColun;

		for (auto& i : Path)
		{
			if (i.Coord.y == y)
			{
				bool ocupied = false;
				for (auto& i2 : screen->Objects)
				{
					if (i.Coord == ((Object*)i2)->Coord)
					{
						ocupied = true;
					}
				}
				if (!ocupied)
					InColun.push_back(i);
			}
		}

		for (int x = 0; x < screen->Limits.x; x++)
		{
			bool Showed = false;

			for (auto& i : InColun)
			{
				if (i.Coord.x == x)
				{
					std::cout << std::setw(4) << (int)i.Coast();
					Showed = true;
				}
			}

			if (!Showed)
				std::cout << std::setw(4) << Grafics(((Object*)screen->screen[x][y].Occupant)->ID);
		}

		std::cout << "\n";
	}
}

void SelfMovableObject::Move()
{
	if (!Path.empty())
	{
		if (((Object*)screen->screen[Path.front().Coord.x][Path.front().Coord.y].Occupant)->ID == Tile::GraficsID::EMPTY)
		{
			screen->screen[Coord.x][Coord.y].Occupant = new Object(Tile::GraficsID::EMPTY, Coord);

			Coord = Path.front().Coord;

			((Object*)screen->screen[Coord.x][Coord.y].Occupant)->~Object();

			screen->screen[Coord.x][Coord.y].Occupant = this;

			CouldntMove = 0;
			Path.pop_front();
		}
		else
		{
			CouldntMove++;
		}
	}
}
