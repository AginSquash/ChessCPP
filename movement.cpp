//
//  movement.cpp
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 07.01.2020.
//

#include "movement.hpp"
#include "types.h"
#include "debug_func.hpp"

extern short figure_to_move_index;
extern float scale;

sf::Vector2f getAbsoluteCoordinate(sf::Vector2f pos)
{
    pos.x = int((pos.x / scale) / 100) * 100 * scale;
    pos.y = int((pos.y / scale) / 100) * 100 * scale;
    return pos;
}

int GetFigureByPosition(chess_figure* p_figures, sf::Vector2f pos) //Функция находит фигуру соотв. координатам
{
    pos = getAbsoluteCoordinate(pos);
    for (int i = 0; i < 32; i++) {
        if (p_figures[i].position == pos) {
            return i;
        }
    }
    return -1;
}

bool GetFigureByPositionBool(chess_figure* p_figures, sf::Vector2f pos) //Функция находит фигуру соотв. координатам
{
    pos = getAbsoluteCoordinate(pos);
    for (int i = 0; i < 32; i++) {
        if (p_figures[i].position == pos) {
            return false;
        }
    }
    return true;
}


bool Possiblemove(chess_figure* p_figures, int j, sf::Vector2f pos)
{

    sf::Vector2f newpos;

    if ( (j > 5 && j < 8)||p_figures[figure_to_move_index].type==b_Rook) { //Черная ладья (Rook)
        newpos = p_figures[j].position;
        if (pos.x > newpos.x && pos.y == newpos.y) {
            while (newpos.x != pos.x) {
                newpos.x += 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos.x == newpos.x) {
                    return true;
                }
            }
        }
        if (pos.x < newpos.x && pos.y == newpos.y) {
            while (newpos.x != pos.x) {
                newpos.x -= 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos.x == newpos.x) {
                    return true;
                }
            }
        }
        if (pos.y > newpos.y && pos.x == newpos.x) {
            while (newpos.y != pos.y) {
                newpos.y += 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos.y == newpos.y) {
                    return true;
                }
            }
        }
        if (pos.y < newpos.y && pos.x == newpos.x) {
            while (newpos.y != pos.y) {
                newpos.y -= 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;

                if (pos.y == newpos.y) {
                    return true;
                }
            }
        }
    }
    if ( (j > 21 && j < 24)||p_figures[figure_to_move_index].type==w_Rook ) { //Белая ладья ладья (Rook)
        newpos = p_figures[j].position;
        if (pos.x > newpos.x && pos.y == newpos.y) {
            while (newpos.x != pos.x) {
                newpos.x += 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos.x == newpos.x) {
                    return true;
                }
            }
        }
        if (pos.x < newpos.x && pos.y == newpos.y) {
            while (newpos.x != pos.x) {
                newpos.x -= 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos.x == newpos.x) {
                    return true;
                }
            }
        }
        if (pos.y > newpos.y && pos.x == newpos.x) {
            while (newpos.y != pos.y) {
                newpos.y += 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos.y == newpos.y) {
                    return true;
                }
            }
        }
        if (pos.y < newpos.y && pos.x == newpos.x) {
            while (newpos.y != pos.y) {
                newpos.y -= 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;

                if (pos.y == newpos.y) {
                    return true;
                }
            }
        }
    }
    if ( (j == 2 || j == 3 || j == 18 || j == 19)&&(p_figures[figure_to_move_index].type==w_Night || p_figures[figure_to_move_index].type==b_Night )) { //2, 3 - черный конь. 18,19 - белый конь
        sf::Vector2f PosNight[8];
        PosNight[0].x = p_figures[j].position.x + 100 * scale;
        PosNight[0].y = p_figures[j].position.y + 200 * scale;
        PosNight[1].x = p_figures[j].position.x - 100 * scale;
        PosNight[1].y = p_figures[j].position.y + 200 * scale;
        PosNight[2].x = p_figures[j].position.x + 100 * scale;
        PosNight[2].y = p_figures[j].position.y - 200 * scale;
        PosNight[3].x = p_figures[j].position.x - 100 * scale;
        PosNight[3].y = p_figures[j].position.y - 200 * scale;
        PosNight[4].x = p_figures[j].position.x + 200 * scale;
        PosNight[4].y = p_figures[j].position.y + 100 * scale;
        PosNight[5].x = p_figures[j].position.x + 200 * scale;
        PosNight[5].y = p_figures[j].position.y - 100 * scale;
        PosNight[6].x = p_figures[j].position.x - 200 * scale;
        PosNight[6].y = p_figures[j].position.y + 100 * scale;
        PosNight[7].x = p_figures[j].position.x - 200 * scale;
        PosNight[7].y = p_figures[j].position.y - 100 * scale;
        for (int i = 0; i < 8; i++) {
            if (PosNight[i] == pos)
            {
                _print("[posible move] POS.x", pos.x);
                _print("[posible move] POS.y", pos.y);
                return true;
            }
        } return false;
    }
    //0,1 - черные слоны . 16, 17 - белые
    if ( (j == 0 || j == 1 || j == 16 || j == 17)&&(p_figures[figure_to_move_index].type==b_Bishop||p_figures[figure_to_move_index].type==w_Bishop) ) {
        newpos = p_figures[j].position;
        if (pos.x > newpos.x && pos.y > newpos.y) {
            while (pos != newpos) {
                newpos.x += 100 * scale;
                newpos.y += 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos == newpos)
                    return true;
            }
        }
        if (pos.x < newpos.x && pos.y < newpos.y) {
            while (pos != newpos) {
                newpos.x -= 100 * scale;
                newpos.y -= 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos == newpos)
                    return true;
            }
        }
        if (pos.x > newpos.x && pos.y < newpos.y) {
            while (pos != newpos) {
                newpos.x += 100 * scale;
                newpos.y -= 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos == newpos)
                    return true;
            }
        }
        if (pos.x < newpos.x && pos.y > newpos.y) {
            while (pos != newpos) {
                newpos.x -= 100 * scale;
                newpos.y += 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos == newpos)
                    return true;
            }
        }
    }
    if  (j == 5 || j == 21) { //5 - черный король. 21 - белый король
        sf::Vector2f PosKing[8];
        PosKing[0].x = p_figures[j].position.x - 100 * scale;
        PosKing[0].y = p_figures[j].position.y - 100 * scale;
        PosKing[1].x = p_figures[j].position.x;
        PosKing[1].y = p_figures[j].position.y - 100 * scale;
        PosKing[2].x = p_figures[j].position.x + 100 * scale;
        PosKing[2].y = p_figures[j].position.y - 100 * scale;
        PosKing[3].x = p_figures[j].position.x + 100 * scale;
        PosKing[3].y = p_figures[j].position.y;
        PosKing[4].x = p_figures[j].position.x + 100 * scale;
        PosKing[4].y = p_figures[j].position.y + 100 * scale;
        PosKing[5].x = p_figures[j].position.x;
        PosKing[5].y = p_figures[j].position.y + 100 * scale;
        PosKing[6].x = p_figures[j].position.x - 100 * scale;
        PosKing[6].y = p_figures[j].position.y + 100 * scale;
        PosKing[7].x = p_figures[j].position.x - 100 * scale;
        PosKing[7].y = p_figures[j].position.y;
        for (int i = 0; i < 8; i++) {
            if (PosKing[i] == pos)
            {
                return true;
            }
        }
        return false;
    }
    // Черная королева - 4, белая - 20
    if ((j == 4 || j == 20)||(p_figures[figure_to_move_index].type==b_Qween)||p_figures[figure_to_move_index].type==w_Qween) {

        newpos = p_figures[j].position;
        if (pos.x > newpos.x && pos.y > newpos.y) {
            while (pos != newpos) {
                newpos.x += 100 * scale;
                newpos.y += 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos == newpos)
                    return true;
            }
        }
        if (pos.x < newpos.x && pos.y < newpos.y) {
            while (pos != newpos) {
                newpos.x -= 100 * scale;
                newpos.y -= 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos == newpos)
                    return true;
            }
        }
        if (pos.x > newpos.x && pos.y < newpos.y) {
            while (pos != newpos) {
                newpos.x += 100 * scale;
                newpos.y -= 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos == newpos)
                    return true;
            }
        }
        if (pos.x < newpos.x && pos.y > newpos.y) {
            while (pos != newpos) {
                newpos.x -= 100 * scale;
                newpos.y += 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos == newpos)
                    return true;
            }
        }
        if (pos.x > newpos.x && pos.y == newpos.y) {
            while (newpos.x != pos.x) {
                newpos.x += 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos.x == newpos.x) {
                    return true;
                }
            }
        }
        if (pos.x < newpos.x && pos.y == newpos.y) {
            while (newpos.x != pos.x) {
                newpos.x -= 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos.x == newpos.x) {
                    return true;
                }
            }
        }
        if (pos.y > newpos.y && pos.x == newpos.x) {
            while (newpos.y != pos.y) {
                newpos.y += 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;
                if (pos.y == newpos.y) {
                    return true;
                }
            }
        }
        if (pos.y < newpos.y && pos.x == newpos.x) {
            while (newpos.y != pos.y) {
                newpos.y -= 100 * scale;
                if (GetFigureByPositionBool(p_figures, newpos) == false)
                    return false;

                if (pos.y == newpos.y) {
                    return true;
                }
            }
        }
    }
    if (j >= 8 && j < 16) { //Черные пешки

        if (p_figures[j].position.y == scale * 100) {
            return ((p_figures[j].position.x == pos.x) && (p_figures[j].position.y == (pos.y - 100 * scale))) || ((p_figures[j].position.x == pos.x) && (p_figures[j].position.y == (pos.y - 200 * scale)));
        }
        newpos = pos;
        if (GetFigureByPositionBool(p_figures, newpos) && (newpos.x == p_figures[j].position.x && newpos.y == p_figures[j].position.y + 100 * scale))
            return true;
    }

    if (j > 23 && j < 32) { //белые пешки
        if (p_figures[j].position.y == scale * 600) {
            if (((p_figures[j].position.x == pos.x) && (p_figures[j].position.y == (pos.y + 100 * scale))) || ((p_figures[j].position.x == pos.x) && (p_figures[j].position.y == (pos.y + 200 * scale)))) {
                return true;
            }
        }
        newpos = pos;
        if (GetFigureByPositionBool(p_figures, newpos) && (newpos.x == p_figures[j].position.x && newpos.y == p_figures[j].position.y - 100 * scale))
            return true;
    }
}

bool figurekillforpawns(chess_figure* p_figures, int field_index, int figure_to_move_index, sf::Vector2f pos, bool isWhiteQueue)
{

    if (figure_to_move_index > 7 && figure_to_move_index < 16) {
        sf::Vector2f newposL;
        newposL.x = p_figures[figure_to_move_index].position.x + 100 * scale;
        newposL.y = p_figures[figure_to_move_index].position.y + 100 * scale;
        sf::Vector2f newposR;
        newposR.x = p_figures[figure_to_move_index].position.x - 100 * scale;
        newposR.y = p_figures[figure_to_move_index].position.y + 100 * scale;
        if (GetFigureByPosition(p_figures, newposL) > 15 && GetFigureByPosition(p_figures, newposL) < 32)
            if (newposL == pos) {
                return true;
            }
        if (GetFigureByPosition(p_figures, newposR) > 15 && GetFigureByPosition(p_figures, newposR) < 32)
            if (newposR == pos) {
                return true;
            }
    }
    if (figure_to_move_index > 23 && figure_to_move_index < 32) {
        sf::Vector2f newposL;
        newposL.x = p_figures[figure_to_move_index].position.x - 100 * scale;
        newposL.y = p_figures[figure_to_move_index].position.y - 100 * scale;
        sf::Vector2f newposR;
        newposR.x = p_figures[figure_to_move_index].position.x + 100 * scale;
        newposR.y = p_figures[figure_to_move_index].position.y - 100 * scale;
        if (GetFigureByPosition(p_figures, newposL) > -1 && GetFigureByPosition(p_figures, newposL) < 16)
            if (newposL == pos) {
                return true;
            }
        if (GetFigureByPosition(p_figures, newposR) > -1 && GetFigureByPosition(p_figures, newposR) < 16)
            if (newposR == pos) {
                return true;
            }
    }
}

void endGame(chess_figure* p_figures)
{
    for (short i = 0; i < 32; i++) {
        p_figures[i].isAlive = false;
    }
}

bool figureKillForRook(chess_figure* p_figures, int field_index, int figure_to_move_index, sf::Vector2f pos, bool isWhiteQueue)
{
    sf::Vector2f newpos;
    newpos = p_figures[figure_to_move_index].position;
    if (figure_to_move_index == 6 || figure_to_move_index == 7|| p_figures[figure_to_move_index].type==b_Rook) {
        if (field_index > 15) {
            if (pos.y == newpos.y && pos.x > newpos.x)
                while (pos.x != newpos.x) {
                    newpos.x += 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }
            if (pos.y == newpos.y && pos.x < newpos.x)
                while (pos.x != newpos.x) {
                    newpos.x -= 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }
            if (pos.x == newpos.x && pos.y > newpos.y)
                while (pos.y != newpos.y) {
                    newpos.y += 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }
            if (pos.x == newpos.x && pos.y < newpos.y)
                while (pos.y != newpos.y) {
                    newpos.y -= 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }
        }
    }
    if (figure_to_move_index == 22 || figure_to_move_index == 23 || p_figures[figure_to_move_index].type==w_Rook) {
        if (field_index < 16) {
            if (pos.y == newpos.y && pos.x > newpos.x)
                while (pos.x != newpos.x) {
                    newpos.x += 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }
            if (pos.y == newpos.y && pos.x < newpos.x)
                while (pos.x != newpos.x) {
                    newpos.x -= 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }
            if (pos.x == newpos.x && pos.y > newpos.y)
                while (pos.y != newpos.y) {
                    newpos.y += 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }
            if (pos.x == newpos.x && pos.y < newpos.y)
                while (pos.y != newpos.y) {
                    newpos.y -= 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }
        }
    }
}

bool figureKillForKnight(chess_figure* p_figures, int field_index, int figure_to_move_index, sf::Vector2f pos, bool isWhiteQueue)
{
    if (figure_to_move_index == 2 || figure_to_move_index == 3 || figure_to_move_index == 18 || figure_to_move_index == 19 || p_figures[figure_to_move_index].type==w_Night || p_figures[figure_to_move_index].type==b_Night) {
        sf::Vector2f PosNight[8];
        PosNight[0].x = p_figures[figure_to_move_index].position.x + 100 * scale;
        PosNight[0].y = p_figures[figure_to_move_index].position.y + 200 * scale;
        PosNight[1].x = p_figures[figure_to_move_index].position.x - 100 * scale;
        PosNight[1].y = p_figures[figure_to_move_index].position.y + 200 * scale;
        PosNight[2].x = p_figures[figure_to_move_index].position.x + 100 * scale;
        PosNight[2].y = p_figures[figure_to_move_index].position.y - 200 * scale;
        PosNight[3].x = p_figures[figure_to_move_index].position.x - 100 * scale;
        PosNight[3].y = p_figures[figure_to_move_index].position.y - 200 * scale;
        PosNight[4].x = p_figures[figure_to_move_index].position.x + 200 * scale;
        PosNight[4].y = p_figures[figure_to_move_index].position.y + 100 * scale;
        PosNight[5].x = p_figures[figure_to_move_index].position.x + 200 * scale;
        PosNight[5].y = p_figures[figure_to_move_index].position.y - 100 * scale;
        PosNight[6].x = p_figures[figure_to_move_index].position.x - 200 * scale;
        PosNight[7].x = p_figures[figure_to_move_index].position.x - 200 * scale;
        PosNight[7].y = p_figures[figure_to_move_index].position.y - 100 * scale;
        for (int i = 0; i < 8; i++) {
            if (PosNight[i] == pos) {
                _print("POS.x", pos.x);
                _print("POS.y", pos.y);
                if (figure_to_move_index < 16 && field_index > 15)
                    return true;
                if (figure_to_move_index > 15 && field_index < 16)
                    return true;
            }
        } return false;
    }
}

bool figureKillForBishop(chess_figure* p_figures, int field_index, int figure_to_move_index, sf::Vector2f pos, bool isWhiteQueue)
{
    sf::Vector2f newpos = p_figures[figure_to_move_index].position;
    if (figure_to_move_index == 0 || figure_to_move_index == 1 || p_figures[figure_to_move_index].type==b_Bishop) {
        if (field_index > 15) {
            if (pos.x > newpos.x && pos.y > newpos.y) {
                while (pos != newpos) {
                    newpos.x += 100 * scale;
                    newpos.y += 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }
            if (pos.x < newpos.x && pos.y < newpos.y) {
                while (pos != newpos) {
                    newpos.x -= 100 * scale;
                    newpos.y -= 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }
            if (pos.x > newpos.x && pos.y < newpos.y) {
                while (pos != newpos) {
                    newpos.x += 100 * scale;
                    newpos.y -= 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }
            if (pos.x < newpos.x && pos.y > newpos.y) {
                while (pos != newpos) {
                    newpos.x -= 100 * scale;
                    newpos.y += 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }
        }
    }
    if (figure_to_move_index == 16 || figure_to_move_index == 17 || p_figures[figure_to_move_index].type==w_Bishop) {
        if (field_index < 16) {
            if (pos.x > newpos.x && pos.y > newpos.y) {
                while (pos != newpos) {
                    newpos.x += 100 * scale;
                    newpos.y += 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }
            if (pos.x < newpos.x && pos.y < newpos.y) {
                while (pos != newpos) {
                    newpos.x -= 100 * scale;
                    newpos.y -= 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }
            if (pos.x > newpos.x && pos.y < newpos.y) {
                while (pos != newpos) {
                    newpos.x += 100 * scale;
                    newpos.y -= 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }
            if (pos.x < newpos.x && pos.y > newpos.y) {
                while (pos != newpos) {
                    newpos.x -= 100 * scale;
                    newpos.y += 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }
        }
    }
}

bool figureKillForKing(chess_figure* p_figures, int field_index, int figure_to_move_index, sf::Vector2f pos, bool isWhiteQueue)
{
    sf::Vector2f PosKing[8];
    PosKing[0].x = p_figures[figure_to_move_index].position.x - 100 * scale;
    PosKing[0].y = p_figures[figure_to_move_index].position.y - 100 * scale;
    PosKing[1].x = p_figures[figure_to_move_index].position.x;
    PosKing[1].y = p_figures[figure_to_move_index].position.y - 100 * scale;
    PosKing[2].x = p_figures[figure_to_move_index].position.x + 100 * scale;
    PosKing[2].y = p_figures[figure_to_move_index].position.y - 100 * scale;
    PosKing[3].x = p_figures[figure_to_move_index].position.x + 100 * scale;
    PosKing[3].y = p_figures[figure_to_move_index].position.y;
    PosKing[4].x = p_figures[figure_to_move_index].position.x + 100 * scale;
    PosKing[4].y = p_figures[figure_to_move_index].position.y + 100 * scale;
    PosKing[5].x = p_figures[figure_to_move_index].position.x;
    PosKing[5].y = p_figures[figure_to_move_index].position.y + 100 * scale;
    PosKing[6].x = p_figures[figure_to_move_index].position.x - 100 * scale;
    PosKing[6].y = p_figures[figure_to_move_index].position.y + 100 * scale;
    PosKing[7].x = p_figures[figure_to_move_index].position.x - 100 * scale;
    PosKing[7].y = p_figures[figure_to_move_index].position.y;
    if (figure_to_move_index == 5 && field_index > 15 ) {
        for (int i = 0; i < 8; i++) {
            if (PosKing[i] == pos) {
                return true;
            }
        } return false;
    }
    if (figure_to_move_index == 21 && field_index < 16) {
        for (int i = 0; i < 8; i++) {
            if (PosKing[i] == pos) {
                return true;
            }
        } return false;
    }
}

bool figureKillForQueen(chess_figure* p_figures, int field_index, int figure_to_move_index, sf::Vector2f pos, bool isWhiteQueue)
{
    sf::Vector2f newpos = p_figures[figure_to_move_index].position;
    if (figure_to_move_index == 4 || p_figures[figure_to_move_index].type==b_Qween) {
        if (field_index > 15) {
            if (pos.y == newpos.y && pos.x > newpos.x)
                while (pos.x != newpos.x) {
                    newpos.x += 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }
            if (pos.y == newpos.y && pos.x < newpos.x)
                while (pos.x != newpos.x) {
                    newpos.x -= 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }
            if (pos.x == newpos.x && pos.y > newpos.y)
                while (pos.y != newpos.y) {
                    newpos.y += 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }
            if (pos.x == newpos.x && pos.y < newpos.y)
                while (pos.y != newpos.y) {
                    newpos.y -= 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }

            if (pos.x > newpos.x && pos.y > newpos.y) {
                while (pos != newpos) {
                    newpos.x += 100 * scale;
                    newpos.y += 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }
            if (pos.x < newpos.x && pos.y < newpos.y) {
                while (pos != newpos) {
                    newpos.x -= 100 * scale;
                    newpos.y -= 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }
            if (pos.x > newpos.x && pos.y < newpos.y) {
                while (pos != newpos) {
                    newpos.x += 100 * scale;
                    newpos.y -= 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }
            if (pos.x < newpos.x && pos.y > newpos.y) {
                while (pos != newpos) {
                    newpos.x -= 100 * scale;
                    newpos.y += 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }
        }
    }
    if (figure_to_move_index == 20 || p_figures[figure_to_move_index].type==w_Qween) {
        if (field_index < 16) {
            if (pos.y == newpos.y && pos.x > newpos.x)
                while (pos.x != newpos.x) {
                    newpos.x += 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }
            if (pos.y == newpos.y && pos.x < newpos.x)
                while (pos.x != newpos.x) {
                    newpos.x -= 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }
            if (pos.x == newpos.x && pos.y > newpos.y)
                while (pos.y != newpos.y) {
                    newpos.y += 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }
            if (pos.x == newpos.x && pos.y < newpos.y)
                while (pos.y != newpos.y) {
                    newpos.y -= 100 * scale;
                    if ((GetFigureByPosition(p_figures, newpos) == field_index))
                        return true;
                    if (GetFigureByPosition(p_figures, newpos) != field_index && GetFigureByPositionBool(p_figures, newpos) == false)
                        return false;
                }

            if (pos.x > newpos.x && pos.y > newpos.y) {
                while (pos != newpos) {
                    newpos.x += 100 * scale;
                    newpos.y += 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }
            if (pos.x < newpos.x && pos.y < newpos.y) {
                while (pos != newpos) {
                    newpos.x -= 100 * scale;
                    newpos.y -= 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }
            if (pos.x > newpos.x && pos.y < newpos.y) {
                while (pos != newpos) {
                    newpos.x += 100 * scale;
                    newpos.y -= 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }
            if (pos.x < newpos.x && pos.y > newpos.y) {
                while (pos != newpos) {
                    newpos.x -= 100 * scale;
                    newpos.y += 100 * scale;
                    if (GetFigureByPositionBool(p_figures, newpos) == false) {
                        if (GetFigureByPosition(p_figures, newpos) == field_index)
                            return true;
                        else
                            return false;
                    }
                }
            }


        }
    }
}
