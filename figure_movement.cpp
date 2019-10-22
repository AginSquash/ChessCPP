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

sf::Vector2f* orignalDesk(chess_figure* p_desk, sf::Vector2f NEW_desk[32], float scale)
{
    scale *= 100;
    
    for (short i = 0; i < 32; i++)
    {
        if (p_desk[i].isAlive)
        {
            NEW_desk[i].x = p_desk[i].position.x / scale;
            NEW_desk[i].y = p_desk[i].position.y / scale;
        } else {
            NEW_desk[i].x = -1;
            NEW_desk[i].y = -1;
        }
    }
    return NEW_desk;
}

bool isPosibleMoves(figure_type figure, sf::Vector2f pos, chess_figure desk[32], float scale )
{
    sf::Vector2f *NEW_desk =  new sf::Vector2f[32];
    orignalDesk( desk, NEW_desk, scale);
    
    pos.x = (pos.x/scale) / 100;
    pos.y = (pos.y/scale) / 100;
    
    for (short i = 0; i < 32; i++)
    {
        _print("desk[x]", NEW_desk[i].x);
        _print("desk[y]", NEW_desk[i].y);
    }
    
    _print("pos[x]", pos.x);
    _print("pos[y]", pos.y);
    
    
    switch (figure) {
        case (b_Qween || w_Qween):
            
            break;
            
        default:
            break;
    }
    
    delete[] NEW_desk;
}
