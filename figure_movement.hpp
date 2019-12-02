//
//  figure_movement.hpp
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 22.10.2019.
//

#ifndef figure_movement_hpp
#define figure_movement_hpp

#include <stdio.h>

#include "DataLoading.h"

bool isPosibleMoves(const figure_type figure,
    sf::Vector2f pos,
    const chess_figure desk[32],
    float scale,
    bool bool_desk[8][8]);
#endif /* figure_movement_hpp */
