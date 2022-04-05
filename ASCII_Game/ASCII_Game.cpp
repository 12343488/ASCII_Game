#include <iostream>
#include <vector>

#include "Screen.h"
#include "Object.h"
#include "Events.h"

int main()
{
    //cria e inicializa a tela, tdos os tiles estão ligados de forma q pode vir e voltar a vontade
    Screen screen(20, 20);


    Object player(Tile::GraficsID::PLAYER, Vec2(0.0f, 0.0f), screen);

    //cria as paredes
    std::vector<Object*> Walls;
    
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            if(!(y > 2 && y < 7 && x > 2 && x < 7))
                Walls.push_back(new Object(Tile::GraficsID::WALL, Vec2(x + 7, y + 5), screen));
        }
    }

    Walls.shrink_to_fit();

    //começo do loop principal
    std::string command;

    while (command != "stop")
    {
        screen.Display();

        command = "";
        std::cout << "\n\n\n> ";
        std::getline(std::cin, command);

        commands(command, screen);
    }
}