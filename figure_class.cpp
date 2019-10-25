//
//  figure_class.cpp
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 25.10.2019.
//

#include "figure_class.hpp"

#include "debug_func.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "types.h"
#include "DataLoading.h"

static std::string PATH = "";

void setResourcePath(std::string PATH_external)
{
    PATH = PATH_external;
}

static float scale = 1.0f;

void setGlobalScale(float scale_external)
{
    scale = scale_external;
}

void figures::LoadSprite( figure_type type ){
       sprite.setTexture(  LoadFigureTexture(type, PATH) );
}

void figures::SetScale(float scale){
    sf::Vector2f targetSize(100.0f * scale, 100.0f * scale);
    this->sprite.setScale(
            targetSize.x / sprite.getLocalBounds().width,
            targetSize.y / sprite.getLocalBounds().height);
}

bool figures::isAlive()
{
    return Alive;
}

void figures::kill()
{
    Alive = false;
}

void figures::setFigureType(figure_type f_type)
{
    type = f_type;
}

figure_type figures::getFigureType()
{
    return type;
}

void figures::Create(figure_type type)
{
    LoadSprite( type );
    SetScale( scale );
}
 
void figures::SetPosition(sf::Vector2f pos)
{
    position = pos;
}

sf::Vector2f figures::GetPosition()
{
    return position;
}

void figures::Move(sf::Vector2f move_to)
{
    sf::Vector2f delta_move = (move_to - position) / scale / 100.0f;
    if (delta_move.x == delta_move.y)
    {
        
        //Значит насикось
        
    } else if (delta_move.y == 0)
    {
    
        //Значит ход по Х
        
    } else if (delta_move.x == 0)
    {
        
        //Значит по Y
        
    } else if ( (type == b_Night) || (type == w_Night) )
    {
        
        //Значит конь
        
    } else {
        _print("Inncorrect move X: ", delta_move.x );
        _print("Inncorrect move Y", delta_move.y );
    }
}
