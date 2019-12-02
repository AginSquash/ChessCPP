//
//  figure_movement.cpp
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 22.10.2019.
//

#include "figure_movement.hpp"

#include "debug_func.hpp"

bool Qween_movement()
{
}

bool getFreePosition(const chess_figure desk[32], float scale, bool bool_desk[8][8])
{
    for (int i = 0; i < 32; i++) {

        short x = (desk[i].position.x / scale) / 100;
        short y = (desk[i].position.y / scale) / 100;

        //_print("desk[i].isAlive", desk[i].isAlive);
        //_print("desk[i].x", x);
        //_print("desk[i].y", y);

        if (desk[i].isAlive) {

            bool_desk[x][y] = true;
        } else {
            bool_desk[x][y] = false;
        }
    }
    return bool_desk;
}

void getNulledMassive(bool bool_desk[8][8])
{
    for (short y = 0; y < 8; y++) {
        for (short x = 0; x < 8; x++) {
            bool_desk[x][y] = false;
        }
    }
}

bool isPosibleMoves(const figure_type figure, sf::Vector2f pos, const chess_figure desk[32], float scale, bool bool_desk[8][8])
{
    _print("PossibleMove loaded", 1);

    pos.x = (pos.x / scale) / 100;
    pos.y = (pos.y / scale) / 100;

    _print("POS X/Y", 1);

    //bool bool_desk[8][8];
    getNulledMassive(bool_desk);

    _print("Without function", bool_desk[0][0]);

    //getFreePosition(desk, scale, bool_desk);

    std::cout << "~~~~~~~~~~~~~~~~" << std::endl;
    for (short y = 0; y < 8; y++) {
        for (short x = 0; x < 8; x++) {
            std::cout << bool_desk[x][y];
        }
        std::cout << std::endl;
    }
    std::cout << "~~~~~~~~~~~~~~~~" << std::endl;

    getFreePosition(desk, scale, bool_desk);

    std::cout << "----------------" << std::endl;
    for (short y = 0; y < 8; y++) {
        for (short x = 0; x < 8; x++) {
            std::cout << bool_desk[x][y];
        }
        std::cout << std::endl;
    }
    std::cout << "----------------" << std::endl;

    return bool_desk;
}
