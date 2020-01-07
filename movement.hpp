//
//  movement.hpp
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 07.01.2020.
//

#ifndef movement_hpp
#define movement_hpp

#include <stdio.h>
#include "types.h"



sf::Vector2f getAbsoluteCoordinate(sf::Vector2f pos);

int GetFigureByPosition(chess_figure* p_figures, sf::Vector2f pos);

bool GetFigureByPositionBool(chess_figure* p_figures, sf::Vector2f pos);

bool Possiblemove(chess_figure* p_figures, int j, sf::Vector2f pos);

bool figurekillforpawns(chess_figure* p_figures, int field_index, int figure_to_move_index, sf::Vector2f pos, bool isWhiteQueue);

void endGame(chess_figure* p_figures);

bool figureKillForRook(chess_figure* p_figures, int field_index, int figure_to_move_index, sf::Vector2f pos, bool isWhiteQueue);

bool figureKillForKnight(chess_figure* p_figures, int field_index, int figure_to_move_index, sf::Vector2f pos, bool isWhiteQueue);

bool figureKillForBishop(chess_figure* p_figures, int field_index, int figure_to_move_index, sf::Vector2f pos, bool isWhiteQueue);

bool figureKillForKing(chess_figure* p_figures, int field_index, int figure_to_move_index, sf::Vector2f pos, bool isWhiteQueue);

bool figureKillForQueen(chess_figure* p_figures, int field_index, int figure_to_move_index, sf::Vector2f pos, bool isWhiteQueue);


#endif /* movement_hpp */
