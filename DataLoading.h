//
// Created by Vlad Vrublevsky on 04/10/2019.
//

#ifndef CHESSCPP_DATALOADING_H
#define CHESSCPP_DATALOADING_H

#include <stdio.h>
#include "figure_class.hpp"
#include "types.h"
#include <SFML/Graphics.hpp>

sf::Texture LoadFigureTexture(figure_type type, std::string PATH);

void LoadFigures( figures f_figures[32]);

#endif //CHESSCPP_DATALOADING_H
