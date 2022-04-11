#include <iostream>
#include <vector>

#include "Screen.h"
#include "Object.h"
#include "Events.h"
#include "PathFindig.h"

int main()
{
    //cria e inicializa a tela, tdos os tiles estão ligados de forma q pode vir e voltar a vontade
    Screen screen(44, 44);


    Object player(Tile::GraficsID::PLAYER, Vec2(21.0f, 21.0f), screen);

    SelfMovableObject enemy1(Tile::GraficsID::ENEMY, Vec2(0.0f, 0.0f), screen);
    SelfMovableObject enemy2(Tile::GraficsID::ENEMY, Vec2(43.0f, 0.0f), screen);
    SelfMovableObject enemy3(Tile::GraficsID::ENEMY, Vec2(0.0f, 43.0f), screen);
    SelfMovableObject enemy4(Tile::GraficsID::ENEMY, Vec2(43.0f, 43.0f), screen);

    std::vector<Object*> enemys;

    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
                enemys.push_back(new SelfMovableObject(Tile::GraficsID::ENEMY, Vec2(x + 1, y + 1), screen));
        }
    }

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
    std::vector<void*> Variables;

    std::string command;

    int show = 0;

    Variables.push_back(&command);
    Variables.push_back(&show);

    while (command != "stop")
    {
        if(show == 0)
            screen.Display();

        if (show == 3)
            ShowPaths(screen);

        command = "";
        std::cout << "\n\n\n> ";
        std::getline(std::cin, command);

        commands(screen, Variables);

        int RecalculatedPath = 0;

        for (auto& i : screen.SelfMovObjects)
        {
            AstarPathFinding(player.Coord, ((SelfMovableObject*)i), screen, show, &RecalculatedPath);
            ((SelfMovableObject*)i)->Move();
        }
    }
}