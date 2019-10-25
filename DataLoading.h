//
// Created by Vlad Vrublevsky on 04/10/2019.
//

#ifndef CHESSCPP_DATALOADING_H
#define CHESSCPP_DATALOADING_H

#include <SFML/Graphics.hpp>
#include "types.h"


sf::Texture LoadFigureTexture(figure_type type, std::string PATH);

chess_figure* LoadFigures(chess_figure* p_figures, std::string PATH, float scale);

#endif //CHESSCPP_DATALOADING_H
