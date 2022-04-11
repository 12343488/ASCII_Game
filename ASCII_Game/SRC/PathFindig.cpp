#include "PathFindig.h"

#include "Object.h"

#define CalculationPerFrame 5

TileExplored::TileExplored(Vec2 Coord, Vec2 Parent, int steps, float modifier, float distance) :  Coord(Coord), Parent(Parent), steps(steps), modifier(modifier), distance(distance)
{		}

float TileExplored::Coast()
{
	return steps + modifier + distance;
}

void AstarPathFinding(Vec2 Target, void* Searcher, Screen& screen, int show, int* RecalculatedPath)
{
	std::unordered_map<Vec2, TileExplored> Explored;
	std::unordered_map<Vec2, TileExplored> Frontier;

	bool UsingOldInformation = false;

	if (((Object*)Searcher)->type == Object::Type::SELFMOVABLE)
	{
		if (((SelfMovableObject*)Searcher)->Path.size() == 0)
		{
			if ((*RecalculatedPath) < CalculationPerFrame)
			{
				Frontier.emplace(((Object*)Searcher)->Coord, TileExplored(((Object*)Searcher)->Coord, Vec2(-1, -1), 0, 0, ((Object*)Searcher)->Coord.Distance(Target)));

				std::cout << "começando do zero 1\t";

				(*RecalculatedPath)++;
			}
		}
		else
		{
			if (((SelfMovableObject*)Searcher)->Path.back().Coord.Distance(Target) < 5 && ((SelfMovableObject*)Searcher)->CouldntMove < 3)
			{
				UsingOldInformation = true;

				Explored.emplace(((Object*)Searcher)->Coord, TileExplored(((Object*)Searcher)->Coord, Vec2(-1, -1), 0, 0, ((Object*)Searcher)->Coord.Distance(Target)));
				Frontier.emplace(((SelfMovableObject*)Searcher)->Path.back().Coord, ((SelfMovableObject*)Searcher)->Path.back());

				for (auto& i : ((SelfMovableObject*)Searcher)->Path)
				{
					if (i.Parent == Vec2(-1))
					{
						Explored.emplace(i.Coord, TileExplored(i.Coord, Vec2(-1, -1), i.steps, i.modifier, i.distance));
					}
					else
					{
						Explored.emplace(i.Coord, i);
					}
				}

				std::cout << "utilizando path antigo\t";
			}
			else
			{
				if ((*RecalculatedPath) < CalculationPerFrame)
				{
					Frontier.emplace(((Object*)Searcher)->Coord, TileExplored(((Object*)Searcher)->Coord, Vec2(-1, -1), 0, 0, ((Object*)Searcher)->Coord.Distance(Target)));

					std::cout << "começando do zero 2\t";

					(*RecalculatedPath)++;
				}
			}
		}
	}
	else
	{
		if ((*RecalculatedPath) < CalculationPerFrame)
		{
			Frontier.emplace(((Object*)Searcher)->Coord, TileExplored(((Object*)Searcher)->Coord, Vec2(-1, -1), 0, 0, ((Object*)Searcher)->Coord.Distance(Target)));

			std::cout << "começando do zero 3\t";

			(* RecalculatedPath)++;
		}
	}

	if ((* RecalculatedPath) > CalculationPerFrame)
	{
		std::cout << "numero de calculos por frame exedido\t";
	}

	bool Found = false;

	int iterations = 0;
	
	while (!Frontier.empty() && !Found)
	{
		iterations++;

		TileExplored* MostPromissing = NULL;

		for (auto& i : Frontier)
		{
			if (MostPromissing == NULL)
			{
				MostPromissing = &i.second;
			}
			
			if (MostPromissing->Coast() > i.second.Coast())
			{
				MostPromissing = &i.second;
			}
		}

		if (MostPromissing == NULL)
		{
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			bool NotVisited = true;
			bool ocupied = false;
			Vec2 Exploring(screen.screen[MostPromissing->Coord.x][MostPromissing->Coord.y].ReachableNeighbours[i].first);

			for (auto& i : screen.Objects)
			{
				if (Exploring == ((Object*)i)->Coord && ((Object*)i)->Coord != Target)
				{
					ocupied = true;
					break;
				}
			}

			if (!ocupied)
			{
				int steps = MostPromissing->steps + 1;
				float modifier = screen.screen[MostPromissing->Coord.x][MostPromissing->Coord.y].ReachableNeighbours[i].second;
				float distance = Exploring.Distance(Target);

				if (Exploring == Target)
				{
					Found = true;
					Explored.emplace(MostPromissing->Coord, *MostPromissing);
					Explored.emplace(Exploring, TileExplored(Exploring, MostPromissing->Coord, steps, modifier, distance));
					break;
				}

				float Coast = steps + modifier + distance;

				if (Frontier.find(Exploring) != Frontier.end())
				{
					if (Frontier.at(Exploring).Coast() > Coast)
					{
						Frontier.at(Exploring) = TileExplored(Exploring, MostPromissing->Coord, steps, modifier, distance);
					}
					NotVisited = false;
				}
				else
				{
					if (Explored.find(Exploring) != Explored.end())
					{
						NotVisited = false;
					}
				}

				if (NotVisited)
				{
					Frontier.emplace(Exploring, TileExplored(Exploring, MostPromissing->Coord, steps, modifier, distance));
				}
			}
		}
		if (!Found)
		{
			Explored.emplace(MostPromissing->Coord, *MostPromissing);

			Frontier.erase(MostPromissing->Coord);
		}
	}

	std::cout << "numero de iterações: " << iterations << std::endl;

	if (show == 1)
	{
		for (int i = 0; i < screen.ScreenHeight; i++)
		{
			std::cout << "\n";
		}

		for (int y = screen.Limits.y - 1; y >= 0; y--)
			{
				std::vector<TileExplored> InColun;

				for (auto& i : Explored)
				{
					if (i.second.Coord.y == y)
					{
						bool ocupied = false;
						for (auto& i2 : screen.Objects)
						{
							if (i.second.Coord == ((Object*)i2)->Coord)
							{
								ocupied = true;
							}
						}
						if (!ocupied)
							InColun.push_back(i.second);
					}
				}

				for (int x = 0; x < screen.Limits.x; x++)
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
						std::cout << std::setw(4) << Grafics(((Object*)screen.screen[x][y].Occupant)->ID);
				}

				std::cout << "\n";
		}
	}

	if (Found)
	{
		std::list<TileExplored> Path;
		bool PathTraced = false;

		Vec2 LastCoord = Target;

		while (!PathTraced)
		{
			if (Explored.find(LastCoord) == Explored.end())
			{
				std::cout << "FUDEU" << std::endl;
				return;
			}

			if (Explored.at(LastCoord).Coord != ((SelfMovableObject*)Searcher)->Coord)
			{
				Path.push_front(Explored.at(LastCoord));
				LastCoord = Path.front().Parent;
			}
			else
			{
				PathTraced = true;
			}
		}

		Path.front().Parent = Vec2(-1);

		if (((Object*)Searcher)->type == Object::Type::SELFMOVABLE)
		{
			if (!UsingOldInformation)
				((SelfMovableObject*)Searcher)->Path = Path;

		}

		if (show == 2)

		{
			for (int i = 0; i < screen.ScreenHeight; i++)
			{
				std::cout << "\n";
			}

			for (int y = screen.Limits.y - 1; y >= 0; y--)
			{
				std::vector<TileExplored> InColun;

				for (auto& i : Path)
				{
					if (i.Coord.y == y)
					{
						bool ocupied = false;
						for (auto& i2 : screen.Objects)
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

				for (int x = 0; x < screen.Limits.x; x++)
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
						std::cout << std::setw(4) << Grafics(((Object*)screen.screen[x][y].Occupant)->ID);
				}

				std::cout << "\n";
			}
		}
	}
	else
	{
		((SelfMovableObject*)Searcher)->Path.clear();

		if (show == 2)
		{
			screen.Display();
		}
	}

	
}

void ShowPaths(Screen& screen)
{
		std::unordered_map<Vec2, Vec2> Paths;

		for (auto& i1 : screen.SelfMovObjects)
		{
			for (auto& i2 : ((SelfMovableObject*)i1)->Path)
			{
				Paths.emplace(i2.Coord, i2.Coord);
			}
		}

		for (int i = 0; i < screen.ScreenHeight; i++)
		{
			std::cout << "\n";
		}

		for (int y = screen.Limits.y - 1; y >= 0; y--)
		{
			std::vector<Vec2> InColun;

			for (auto& i : Paths)
			{
				if (i.first.y == y)
				{
					bool ocupied = false;

					for (auto& i2 : screen.Objects)
					{
						if (i.first == ((Object*)i2)->Coord)
						{
							ocupied = true;
						}
					}
					if (!ocupied)
						InColun.push_back(i.first);
				}
			}

			for (int x = 0; x < screen.Limits.x; x++)
			{
				bool Showed = false;

				for (auto& i : InColun)
				{
					if (i.x == x)
					{
						std::cout << std::setw(4) << " p ";
						Showed = true;
					}
				}

				if (!Showed)
					std::cout << std::setw(4) << Grafics(((Object*)screen.screen[x][y].Occupant)->ID);
			}

			std::cout << "\n";
		}
}

