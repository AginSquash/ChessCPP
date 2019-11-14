//
//  types.h
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 25.10.2019.
//

#ifndef types_h
#define types_h

#include "SFML/Graphics.hpp"

enum figure_type {

    BLANK = -1,

    b_Bishop = 0,
    b_King   = 1,
    b_Night  = 2, //Конь
    b_Pawn   = 3,
    b_Qween  = 4,
    b_Rook   = 5,

    w_Bishop = 6,
    w_King   = 7,
    w_Night  = 8,
    w_Pawn   = 9,
    w_Qween = 10,
    w_Rook  = 11

};

struct chess_figure //Структура (надеюсь) будет использованна в дальнейшем
{
    sf::Vector2f position;
    sf::Texture texture;
    figure_type type; // что именно за фигруа (пешка, конь и т.д.) Будет использоваться для опознания фигруы по координатам
    bool isAlive = true;
};


#endif /* types_h */
