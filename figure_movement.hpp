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

sf::Vector2f* orignalDesk(chess_figure* p_desk, sf::Vector2f NEW_desk[32], float scale);

bool isPosibleMoves(figure_type figure, sf::Vector2f pos, chess_figure desk[32], float scale );
#endif /* figure_movement_hpp */
