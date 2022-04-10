#include "Events.h"

void commands(std::string& command, Screen& screen, std::vector<void*> Variables)
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

	if (command == "move")
	{
		bool decided = false;

		while (!decided)
		{
			std::cout << "\n\nQual Direção?\n\nDigite H para ajuda\n\n> ";
			std::getline(std::cin, command);

			if (command == "H" || command == "h")
			{
				std::cout << "\n\nW - para ir para frente / subir\nS - para ir para tras / descer\nA - para ir para a esquerda\nD - para ir para a direita\n\n";
			}

			Vec2 directions(0, 0);

			if ((((command[0] == 'W') || (command[0] == 'w') || (command[0] == 'S') || (command[0] == 's'))  &&
				 ((command[1] == 'W') || (command[1] == 'w') || (command[1] == 'S') || (command[1] == 's'))) ||
				(((command[0] == 'D') || (command[0] == 'd') || (command[0] == 'A') || (command[0] == 'a'))  &&
				 ((command[1] == 'D') || (command[1] == 'd') || (command[1] == 'A') || (command[1] == 'a'))))
			{
				command = command[0];
			}

			if (command[0] == 'W' || command[0] == 'w')
			{
				directions.y = 1;
				decided = true;
			}

			if (command[0] == 'S' || command[0] == 's')
			{
				directions.y = -1;
				decided = true;
			}

			if (command[0] == 'D' || command[0] == 'd')
			{
				directions.x = 1;
				decided = true;
			}

			if (command[0] == 'A' || command[0] == 'a')
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
	if (command == "teleport")
	{

		Vec2 Destination;

		std::cout << "\n\ndigite a coordenada x:\n> ";
		std::getline(std::cin, command);
		ValidadeInput(command, Destination.x);

		if (Destination.x >= screen.Limits.x)
		{
			Destination.x = screen.Limits.x - 1;
		}

		if (Destination.x < 0)
		{
			Destination.x = 0;
		}

		std::cout << "\ndigite a coordenada y:\n> ";
		std::getline(std::cin, command);
		ValidadeInput(command, Destination.y);

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

	if (command == "show path result")
	{
		if (*((int*)Variables[0]) == 1)
		{
			*((int*)Variables[0]) = 0;
		}
		else
		{
			*((int*)Variables[0]) = 1;
		}
	}

	if (command == "show path")
	{
		if (*((int*)Variables[0]) == 2)
		{
			*((int*)Variables[0]) = 0;
		}
		else
		{
			*((int*)Variables[0]) = 2;
		}
	}
}
