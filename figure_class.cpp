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

class chess_figure_TESTCLASS
{
public:
    bool White;
    bool isAlive();
    void kill();
    void LoadSprite( figure_type type );
    void SetScale(float scale);
    void setFigureType( figure_type f_type );
    figure_type getFigureType();
    void SetPosotion( sf::Vector2f pos );
    sf::Vector2f GetPosition();
    
    void Create( figure_type type, float scale );
    
    void Move(sf::Vector2f move_to);
    
    
private:
    bool Alive = true;
    float scale = 1.0f;
    sf::Sprite sprite;
    figure_type type = BLANK;
    sf::Vector2f position;
};

void chess_figure_TESTCLASS::LoadSprite( figure_type type ){
       sprite.setTexture(  LoadFigureTexture(type, PATH) );
}

void chess_figure_TESTCLASS::SetScale(float scale){
    sprite.scale(scale, scale);
}

bool chess_figure_TESTCLASS::isAlive()
{
    return Alive;
}

void chess_figure_TESTCLASS::kill()
{
    Alive = false;
}

void chess_figure_TESTCLASS::setFigureType(figure_type f_type)
{
    type = f_type;
}

figure_type chess_figure_TESTCLASS::getFigureType()
{
    return type;
}

void chess_figure_TESTCLASS::Create(figure_type type, float scale_external)
{
    scale = scale_external;
    LoadSprite( type );
    SetScale( scale );
}

void chess_figure_TESTCLASS::SetPosotion(sf::Vector2f pos)
{
    position = pos;
}

sf::Vector2f chess_figure_TESTCLASS::GetPosition()
{
    return position;
}

void chess_figure_TESTCLASS::Move(sf::Vector2f move_to)
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
