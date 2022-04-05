#include "Events.h"

void commands(std::string& command, Screen& screen)
{
	Object* Player = NULL;

	for (Object* it : Object::Objects)
	{
		if (it->ID == Tile::GraficsID::PLAYER)
		{
			Player = it;
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

			for (int i = 0; (i < command.size()) || (i < 2); i++)
			{
				if (command[i] == 'W' || command[i] == 'w')
				{
					directions.y = 1;
					decided = true;
					break;
				}

				if (command[i] == 'S' || command[i] == 's')
				{
					directions.y = -1;
					decided = true;
					break;
				}

				if (command[i] == 'D' || command[i] == 'd')
				{
					directions.x = 1;
					decided = true;
					break;
				}

				if (command[i] == 'A' || command[i] == 'a')
				{
					directions.x = -1;
					decided = true;
					break;
				}
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
}
