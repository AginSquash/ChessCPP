//
//  figure_class.cpp
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 25.10.2019.
//

#include "figure_class.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"

class chess_figure_TESTCLASS
{
public:
    bool isAlive();
    void kill();
    void LoadSprite( std::string texture_path);
    void SetScale(float scale);
    
    
private:
    bool Alive = true;
    sf::Sprite sprite;
};

void chess_figure_TESTCLASS::LoadSprite( std::string texture_path){
       sf::Texture texture;
       texture.loadFromFile(texture_path);
       sprite.setTexture(texture);
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
