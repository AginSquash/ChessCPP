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


bool orignalDeskBOOL(chess_figure* p_desk, float scale, bool** &table )
{
    scale *= 100;
    
    //bool table[8][8]; // = new bool[8][8];
    
    for (short i = 0; i < 32; i++)
    {
        short x = p_desk[i].position.x / scale;
        short y = p_desk[i].position.y / scale;
        
        if (p_desk[i].isAlive)
        {
            
            table[x][y] = true;
            
        } else {
            
            table[x][y] = false;
        }
    }
    return table;
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
    
   /* for (short i = 0; i < 32; i++)
    {
        _print("desk[x]", NEW_desk[i].x);
        _print("desk[y]", NEW_desk[i].y);
    }
    
    _print("pos[x]", pos.x);
    _print("pos[y]", pos.y);
    */
    
    bool **table = new bool *[8];
    
    orignalDeskBOOL(desk, scale, table);
    
    for (short y = 0; y < 8; y++ )
    {
        for (short x = 0; x < 8; x++ )
        {
            std::cout << table[x][y];
        }
        std::cout << std::endl;
    }
    
    
    switch (figure) {
        case (b_Qween || w_Qween):
            
            break;
            
        default:
            break;
    }
    
    delete[] NEW_desk;
    
    for (int i = 0; i < 8; i++) {
        delete[] table[i];
    }
    delete[] table;
}
