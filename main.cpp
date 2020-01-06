#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#include "DataLoading.h"
#include "configWorker.h"
#include "figure_movement.hpp"
#include "settings.hpp"

#include "figure_movement.hpp"

//#define WINDOWS  //TODO Откоментируй при комплияции под винду
//#define DEBUG

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#define PATH std::string("/")
#endif

#ifdef __APPLE__ || __unix__
#include <unistd.h>
#define GetCurrentDir getcwd
#define PATH std::string("/.ChessCPP/")
#endif

float scale = 0.5f;
//      Небольшой экскурс:
//      предлагаю хранить в массиве не имена файлов/фигур, а соотв. им занчение ИЛИ значение типа figure_type.
//      Например вместо "bB" испольщовать 0 (ИЛИ b_Bishop), "bK" -> 1 и т.д.

const float kegle2pixels = 0.431; // Для соот. шрифта и пикселей

short figure_to_move_index = -1; // Индекс фигуры которую мы перетаскиваем

std::string GetCurrentWorkingDir(void)
{ //Получение текущей директории
    char buff[FILENAME_MAX];
    GetCurrentDir(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    return current_working_dir;
}

//int desk[8][8]; остатки какой то более развитой цивилизации.

void inputInSave(int IndexFigure, sf::Vector2f pos, int FieldIndex, ofstream* ChessMoves)
{

#ifdef WINDOWS
    *ChessMoves << "Figure " << IndexFigure << "\t"
                << "x =" << pos.x << "\t"
                << "y=" << pos.y << "\n";
    if (FieldIndex != 0)
        *ChessMoves << "Figure " << FieldIndex << " is die \n";
#endif
};

void drawField(chess_figure* p_figures, sf::RenderWindow* window)
{
    for (int i = 0; i < 32; i++) {
        if (p_figures[i].isAlive) {
            sf::Sprite sprite(p_figures[i].texture);

            sf::Vector2f targetSize(100.0f * scale, 100.0f * scale); //целевой размер
            sprite.setScale(
                targetSize.x / sprite.getLocalBounds().width,
                targetSize.y / sprite.getLocalBounds().height);

            sprite.setPosition(p_figures[i].position);
            window->draw(sprite);
        }
    }
}

sf::Sprite& drawChessDesk(std::string resource_path)
{

    static sf::Texture texture;
    if (!texture.loadFromFile(resource_path + "background.png")) {
        printf("Loading chessdesk is fail\n");
    }
    static sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Vector2f targetSize(800.0f * scale, 800.0f * scale); //целевой размер

    sprite.setScale(
        targetSize.x / sprite.getLocalBounds().width,
        targetSize.y / sprite.getLocalBounds().height); // Подгоняет текстуру шахматной доски под размер окна.

    return sprite;
}

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
    int locationForMove;
    sf::Vector2f newpos;
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
    if (j > 5 && j < 8) { //Черная ладья (Rook)
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
    if (j > 21 && j < 24) { //Белая ладья ладья (Rook)
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
    if (j == 2 || j == 3 || j == 18 || j == 19) {
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
                return true;
        }
    }
    //0,1 - черные слоны . 16, 17 - белые
    if (j == 0 || j == 1 || j == 16 || j == 17) {
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
    if (j == 5 || j == 21) {
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
                return true;
        }
    }
    // Черная королева - 4, белая - 20
    if (j == 4 || j == 20) {

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
        if (GetFigureByPosition(p_figures, newposL) > 15 && GetFigureByPosition(p_figures, newposL) < 31)
            if (newposL == pos) {
                return true;
            }
        if (GetFigureByPosition(p_figures, newposR) > 15 && GetFigureByPosition(p_figures, newposR) < 31)
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
    if (figure_to_move_index == 6 || figure_to_move_index == 7) {
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
    if (figure_to_move_index == 22 || figure_to_move_index == 23) {
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
    if (figure_to_move_index == 2 || figure_to_move_index == 3 || figure_to_move_index == 18 || figure_to_move_index == 19) {
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
                if (figure_to_move_index < 16 && field_index > 15)
                    return true;
                if (figure_to_move_index > 15 && field_index < 16)
                    return true;
            }
        }
    }
}

bool figureKillForBishop(chess_figure* p_figures, int field_index, int figure_to_move_index, sf::Vector2f pos, bool isWhiteQueue)
{
    sf::Vector2f newpos = p_figures[figure_to_move_index].position;
    if (figure_to_move_index == 0 || figure_to_move_index == 1) {
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
    if (figure_to_move_index == 16 || figure_to_move_index == 17) {
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
    if (figure_to_move_index == 5 && field_index > 15) {
        for (int i = 0; i < 8; i++) {
            if (PosKing[i] == pos) {
                return true;
            }
        }
    }
    if (figure_to_move_index == 21 && field_index < 16) {
        for (int i = 0; i < 8; i++) {
            if (PosKing[i] == pos) {
                return true;
            }
        }
    }
}

bool figureKillForQueen(chess_figure* p_figures, int field_index, int figure_to_move_index, sf::Vector2f pos, bool isWhiteQueue)
{
    sf::Vector2f newpos = p_figures[figure_to_move_index].position;
    if (figure_to_move_index == 4) {
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
    if (figure_to_move_index == 20) {
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

void ChooseTypeOfFigure (chess_figure* p_figures,int figure_to_move_index){
    std::cout << "You can change type of figure. Choose new type.";
    std::cout << "Example of your anwser: [first word of your color]_NewFigure - b.Bishop \n If you want to choose Knight, you should write Night";


    string newtype;
    cin >> newtype;

    if(newtype == "b_Bishop") {
        p_figures[figure_to_move_index].type = b_Bishop; //Хотел сделать через swtich, но оно не хотело работать
        p_figures[figure_to_move_index].texture = LoadFigureTexture(b_Bishop, PATH);
    }

    if(newtype == "w_Bishop") {
        p_figures[figure_to_move_index].type = w_Bishop;
        p_figures[figure_to_move_index].texture = LoadFigureTexture(w_Bishop, PATH);
    }
    if(newtype == "b_Night") {
        p_figures[figure_to_move_index].type = b_Night;
        p_figures[figure_to_move_index].texture = LoadFigureTexture(w_Night, PATH);
    }
    if(newtype == "w_Night") {
        p_figures[figure_to_move_index].type = w_Night;
        p_figures[figure_to_move_index].texture = LoadFigureTexture(b_Night, PATH);
    }
    if(newtype == "b_Qween") {
        p_figures[figure_to_move_index].type = b_Qween;
        p_figures[figure_to_move_index].texture = LoadFigureTexture(b_Qween, PATH);
    }
    if(newtype == "w_Qween") {
        p_figures[figure_to_move_index].type = w_Qween;
        p_figures[figure_to_move_index].texture = LoadFigureTexture(w_Qween, PATH);
    }
    if(newtype == "b_Rook") {
        p_figures[figure_to_move_index].type = b_Rook;
        p_figures[figure_to_move_index].texture = LoadFigureTexture(b_Rook, PATH);
    }
    if(newtype == "w_Rook") {
        p_figures[figure_to_move_index].type = w_Rook;
        p_figures[figure_to_move_index].texture = LoadFigureTexture(w_Rook, PATH);
    }
}
void ChangeFigureType(chess_figure* p_figures, int figure_to_move_index){
    ChooseTypeOfFigure(p_figures, figure_to_move_index);




}
float getShift(std::string text)
{
    int len = text.length();
    float shift = (len * kegle2pixels * 30) / 2;
    return shift;
}

void figureKill(chess_figure* p_figures, short field_index, short f1igure_to_move_index, sf::Vector2f pos)
{
    p_figures[field_index].isAlive = false; // ставим figure_to_move_index
    p_figures[field_index].position = sf::Vector2f(1100.0f * scale, 1100.0f * scale); // Переносим за карту
    p_figures[figure_to_move_index].position = pos;
}

int main()
{

    //Получаем рабочую директорию (windows/Unix-like)
    std::string path_to_workdir = GetCurrentWorkingDir();

    //Создаем ОС-зависимую переменные (пути к ресурсам)
    std::string resource_path = path_to_workdir + PATH + "resources/";

    //Создание окна лаунчера
    sf::RenderWindow settings(sf::VideoMode(400, 400), "Settings");
    settings.setFramerateLimit(30);

    //Загрузка шрифта
    sf::Font font;
    font.loadFromFile(resource_path + "sansation.ttf");

    //Запуск лаунчера
    main_settings(&settings, resource_path, &font);

    ofstream ChessMoves(resource_path + "Save.txt", ios_base::trunc); // Связываем класс с файлом и чистим его. Пока это тестовый файл, потом поменяем.
    ofstream filesave(resource_path + "fuck_file.txt", ios_base::trunc); //Описание fuck_file есть в документации

    map<string, string> config = loadConfig(resource_path); // Подгружаем конфиг

    std::string chess_type;
    for (map<string, string>::iterator it = config.begin(); it != config.end(); it++) //Обработка конфига
    {
        cout << "Key: " << it->first << endl;
        cout << "Value: " << it->second << endl;

        string key = it->first;
        string value = it->second;

        if (key == "scale") {
            scale = atof(value.c_str()); // Перевод стринг в флоат
        }
        if (key == "texture_pack") {
            chess_type = value;
        }
    }

    sf::RenderWindow window(sf::VideoMode(800 * scale, 900 * scale), "ChessCPP");

    window.setFramerateLimit(5);

    //Функция из "configWorker.cpp". Читает конфиг и возвращает нужную папку с теустурами шахмат
    // (т.е. chess24, wikipedia и т.д.)
    //std::string chess_type = getChessType( resource_path );

    //Создаем ОС-зависимую переменные (пути к текстурам)
    std::string textures_path = path_to_workdir + PATH + "resources/textures/" + chess_type + "/";

    sf::Sprite chessdesk = drawChessDesk(resource_path); //Думаю так это будет лучше выглядеть

    sf::Texture backBar_texture;
    backBar_texture.loadFromFile(resource_path + "backbar.png");
    sf::Sprite backBar(backBar_texture);
    backBar.setScale(scale, scale);
    backBar.setPosition(0.0f, 800.0f * scale);

    sf::Texture selected_texture;
    selected_texture.loadFromFile(resource_path + "selected.png");
    sf::Sprite selected(selected_texture);
    selected.setScale(scale, scale);

    //Создание шахмат
    chess_figure* p_figures = new chess_figure[32];
    LoadFigures(p_figures, textures_path, scale);

    //isPosibleMoves(b_Qween, sf::Vector2f(0, 0), p_figures, scale);

    sf::Clock clock; //Запускаем часы
    clock.restart();

    //Таймер
    sf::Text time;
    time.setFont(font);
    time.setPosition(375 * scale, 825 * scale);
    time.setCharacterSize(36 * scale);

    //Прогресс
    sf::Text progress;
    progress.setFont(font);
    progress.setPosition(50 * scale, 830 * scale);
    progress.setCharacterSize(30 * scale);

    //Popup
    sf::Texture texture;
    texture.loadFromFile(resource_path + "popup.png");
    sf::Sprite popup(texture);
    popup.setScale(scale, scale);
    popup.setPosition(0.0f, 800.0f * scale);

    sf::Text popup_text;
    popup_text.setFont(font);
    popup_text.setCharacterSize(30 * scale);
    popup_text.setFillColor(sf::Color::Black);
    bool isPopupShow = false;
    int popup_time = -1;

    //sf::Vector2f settings_coordinate = sf::Vector2f(700 * scale, 800 * scale );

    bool isClicked = false; // Перемнная, которая хранит состояние мышки. Если false - то это "первый" клик.
        // Если true - то это "второй" клик, а значит нужно передвинуть фигуру выбранную на первом клике
        // в(???) координаты второго клика

    bool isWhiteQueue = true;

    bool freePositions[8][8];

    while (window.isOpen()) {
        sf::Time elapsed = clock.getElapsedTime(); //Получаем время со старта

        int sec = int(elapsed.asSeconds()); //переводим в секунды
        int min = int(sec / 60);
        sec -= min * 60;

        time.setString(std::to_string(min) + ":" + std::to_string(sec)); //Составляем строку
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed: //Если закрываем окно
                window.close();
                break;

            case sf::Event::MouseButtonReleased: //Если нажимем кнопку на мыш(и)
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse_world = sf::Mouse::getPosition(window); //Получаем координаты мышки на экране
                    sf::Vector2f pos = window.mapPixelToCoords(mouse_world); //Переводим в пиксели

                    pos = getAbsoluteCoordinate(pos);

                    if (!isClicked) { //Если это "первый" клик
                        figure_to_move_index = GetFigureByPosition(p_figures, pos);
                        if (figure_to_move_index == -1)
                        {
                            break;
                        }
                        if ((figure_to_move_index < 16) && (isWhiteQueue)) {
                            popup_text.setString(
                                "The white side makes a move!");
                            float shift = getShift("The white side makes a move!");
                            popup_text.setPosition((400 - shift) * scale, 825 * scale);
                            isPopupShow = true;
                            popup_time = int(elapsed.asSeconds()) + 5;
                            break;
                        }

                        if ((figure_to_move_index > 15) && (!isWhiteQueue)) {
                            popup_text.setString(
                                "The black side makes a move!");
                            float shift = getShift("The black  side makes a move!");
                            popup_text.setPosition((400 - shift) * scale, 825 * scale);
                            isPopupShow = true;
                            popup_time = int(elapsed.asSeconds()) + 5;
                            break;
                        }
                        selected.setPosition(p_figures[figure_to_move_index].position); // Подсвечимваем выбранную область
                        // (дебаг или оставить?)
                        isClicked = true;

                        isPosibleMoves(p_figures[figure_to_move_index].type, pos, p_figures, scale, freePositions);

                    } else {

                        short field_index = GetFigureByPosition(p_figures, pos); // Получаем фигуру по координатам нажатия
                        if ((figure_to_move_index != -1) && (p_figures[figure_to_move_index].position != pos) && ((figure_to_move_index < 16) && ( field_index > 15 || field_index == -1  )||(figure_to_move_index > 15) && ( field_index < 16 ) ) ) { // Если мы до этого выбрали пустую область - не стоит что-либо делать

                            
                            if (field_index == -1) // Если GetFigureByPosition возвращает -1, значит мы нажимаем на
                            //      пустую клетку
                            {
                                if (Possiblemove(p_figures, figure_to_move_index, pos)) {
                                    p_figures[figure_to_move_index].position = pos;
                                    if (p_figures[figure_to_move_index].position.y == 0 || p_figures[figure_to_move_index].position.y == 700*scale){
                                        ChangeFigureType(p_figures, figure_to_move_index);
                                    }
                                    inputInSave(figure_to_move_index, pos, 0, &ChessMoves);
                                } else {
                                    break;
                                }

                            }
                            if (field_index != -1) {
                                if (((figure_to_move_index > 7 && figure_to_move_index < 16) || (figure_to_move_index > 23 && figure_to_move_index < 31)) && (figurekillforpawns(p_figures, field_index, figure_to_move_index, pos, isWhiteQueue))) {
                                    figureKill(p_figures, field_index, figure_to_move_index, pos);
                                }
                                if ((figure_to_move_index == 6 || figure_to_move_index == 7 || figure_to_move_index == 22 || figure_to_move_index == 23) && figureKillForRook(p_figures, field_index, figure_to_move_index, pos, isWhiteQueue)) {
                                    figureKill(p_figures, field_index, figure_to_move_index, pos);
                                }

                                if ((figure_to_move_index == 2 || figure_to_move_index == 3 || figure_to_move_index == 18 || figure_to_move_index == 19) && figureKillForKnight(p_figures, field_index, figure_to_move_index, pos, isWhiteQueue))
                                    figureKill(p_figures, field_index, figure_to_move_index, pos);

                                if ((figure_to_move_index == 0 || figure_to_move_index == 1 || figure_to_move_index == 16 || figure_to_move_index == 17) && figureKillForBishop(p_figures, field_index, figure_to_move_index, pos, isWhiteQueue))
                                    figureKill(p_figures, field_index, figure_to_move_index, pos);

                                if ((figure_to_move_index == 21 || figure_to_move_index == 5) && figureKillForKing(p_figures, field_index, figure_to_move_index, pos, isWhiteQueue))
                                    figureKill(p_figures, field_index, figure_to_move_index, pos);

                                if ((figure_to_move_index == 20 || figure_to_move_index == 4) && figureKillForQueen(p_figures, field_index, figure_to_move_index, pos, isWhiteQueue))
                                    figureKill(p_figures, field_index, figure_to_move_index, pos);
                            }

                            // isWhiteQueue != isWhiteQueue - почему-то не работает,
                            // приходится через костыли
                            if (isWhiteQueue) //Чет плюсы меня огорчают
                            {
                                isWhiteQueue = false;
                            } else {
                                isWhiteQueue = true;
                            }
                            isClicked = false;
                        }
                    }
                }
                if (!p_figures[5].isAlive) {
                    popup_text.setString(
                        "White win!");
                    float shift = getShift("White win!");
                    popup_text.setPosition((400 - shift) * scale, 825 * scale);
                    isPopupShow = true;
                    popup_time = int(elapsed.asSeconds()) + 1000;
                    endGame(p_figures);
                    break;
                }

                if (!p_figures[21].isAlive) {
                    popup_text.setString(
                        "Black win!");
                    float shift = getShift("Black win!");
                    popup_text.setPosition((400 - shift) * scale, 825 * scale);
                    isPopupShow = true;
                    popup_time = int(elapsed.asSeconds()) + 1000;
                    endGame(p_figures);
                    break;
                }
                break;

            default:
                break;
            }
        }

        if (isWhiteQueue) {
            progress.setString("White side move!");
        } else {
            progress.setString("Black side move!");
        }

        window.clear();
        window.draw(chessdesk);
        window.draw(backBar);
        drawField(p_figures, &window);

        if (isClicked) {
            window.draw(selected);
        }
        window.draw(time);
        window.draw(progress);

        if (isPopupShow) {
            if (int(elapsed.asSeconds()) >= popup_time) {
                isPopupShow = false;
            }
            window.draw(popup);
            window.draw(popup_text);
        }
        window.display();
    }
    window.close();

#ifdef WINDOWS
    for (int i = 0; i < 32; i++) {
        filesave << "figure_type[" << i << "] = " << p_figures[i].position.x << "\t" << p_figures[i].position.y << "\tIs live - " << p_figures[i].isAlive << "\n";
    }
#endif

    filesave.close();
    ChessMoves.close();

    delete[] p_figures;
    return EXIT_SUCCESS;
}
