//
//  figure_rules.cpp
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 25.10.2019.
//

#include "figure_rules.hpp"
#include "SFML/System/Vector2.hpp"

void Qween(sf::Vector2f pos)
{
}

bool getRules(figure_type type, sf::Vector2f delta_pos)
{
    switch (type) {
    case (b_Qween || w_Qween):

        //Проверка поля
        return true;

        break;

    default:
        break;
    }
}
