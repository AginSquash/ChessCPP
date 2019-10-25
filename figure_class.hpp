//
//  figure_class.hpp
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 25.10.2019.
//

#ifndef figure_class_hpp
#define figure_class_hpp

#include <stdio.h>

#include <iostream>
#include "types.h"

void setResourcePath(std::string PATH_external);
void setGlobalScale(float scale_external);

class figures
{
public:
    bool White;
    bool isAlive();
    void kill();
    void LoadSprite( figure_type type );
    void SetScale(float scale);
    void setFigureType( figure_type f_type );
    figure_type getFigureType();
    void SetPosition( sf::Vector2f pos );
    sf::Vector2f GetPosition();
    
    void Create( figure_type type);
    
    void Move(sf::Vector2f move_to);
    
    
//private:
    bool Alive = true;
    float scale = 1.0f;
    sf::Sprite sprite;
    figure_type type = BLANK;
    sf::Vector2f position;
};

#endif /* figure_class_hpp */
