#include "Events.h"

void commands(Screen& screen, std::vector<void*> Variables)
{
	Object* Player = NULL;

	for (void* it : screen.Objects)
	{
		if (((Object*)it)->ID == Tile::GraficsID::PLAYER)
		{
			Player = ((Object*)it);
			break;
		}
	}

	if (*((std::string*)Variables[0]) == "move")
	{
		bool decided = false;

		while (!decided)
		{
			std::cout << "\n\nQual Direção?\n\nDigite H para ajuda\n\n> ";
			std::getline(std::cin, *((std::string*)Variables[0]));

			if (*((std::string*)Variables[0]) == "H" || *((std::string*)Variables[0]) == "h")
			{
				std::cout << "\n\nW - para ir para frente / subir\nS - para ir para tras / descer\nA - para ir para a esquerda\nD - para ir para a direita\n\n";
			}

			Vec2 directions(0, 0);

			if ((*((std::string*)Variables[0]))[0] == 'W' || (*((std::string*)Variables[0]))[0] == 'w')
			{
				directions.y = 1;
				decided = true;
			}

			if ((*((std::string*)Variables[0]))[0] == 'S' || (*((std::string*)Variables[0]))[0] == 's')
			{
				directions.y = -1;
				decided = true;
			}

			if ((*((std::string*)Variables[0]))[0] == 'D' || (*((std::string*)Variables[0]))[0] == 'd')
			{
				directions.x = 1;
				decided = true;
			}

			if ((*((std::string*)Variables[0]))[0] == 'A' || (*((std::string*)Variables[0]))[0] == 'a')
			{
				directions.x = -1;
				decided = true;
			}
		

			if (Player != NULL)
			{
				Player->Move(directions);
			}
		}
		return;
	}

#ifdef _DEBUG
	if (*((std::string*)Variables[0]) == "teleport")
	{

		Vec2 Destination;

		std::cout << "\n\ndigite a coordenada x:\n> ";
		std::getline(std::cin, (*((std::string*)Variables[0])));
		ValidadeInput((*((std::string*)Variables[0])), Destination.x);

		if (Destination.x >= screen.Limits.x)
		{
			Destination.x = screen.Limits.x - 1;
		}

		if (Destination.x < 0)
		{
			Destination.x = 0;
		}

		std::cout << "\ndigite a coordenada y:\n> ";
		std::getline(std::cin, (*((std::string*)Variables[0])));
		ValidadeInput((*((std::string*)Variables[0])), Destination.y);

		if (Destination.y >= screen.Limits.y)
		{
			Destination.y = screen.Limits.y - 1;
		}

		if (Destination.y < 0)
		{
			Destination.y = 0;
		}

		if (Player != NULL)
			Player->Teleport(Destination);

		return;
	}
#endif // DEBUG

	if ((*((std::string*)Variables[0])) == "show path result")
	{
		if (*((int*)Variables[1]) == 1)
		{
			*((int*)Variables[1]) = 0;
		}
		else
		{
			*((int*)Variables[1]) = 1;
		}
	}

	if ((*((std::string*)Variables[0])) == "show path")
	{
		if (*((int*)Variables[1]) == 2)
		{
			*((int*)Variables[1]) = 0;
		}
		else
		{
			*((int*)Variables[1]) = 2;
		}
	}

	if ((*((std::string*)Variables[0])) == "show all paths")
	{
		if (*((int*)Variables[1]) == 3)
		{
			*((int*)Variables[1]) = 0;
		}
		else
		{
			*((int*)Variables[1]) = 3;
		}
	}
}
