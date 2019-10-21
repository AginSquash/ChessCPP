//
//  settings.cpp
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 21.10.2019.
//
#include "settings.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

#include "debug_func.hpp"

//sf::RenderWindow settings (sf::VideoMode(400.0f, 400.0f), "settings" );

int main_settings(sf::RenderWindow *settings, std::string path, sf::Font *font)
{

    std::cout << "Open settings" << std::endl;
    // Start the game loop
    
    sf::Texture background_texture;
    background_texture.loadFromFile(path + "launcher_background.png");
    sf::Sprite background(background_texture);
    
    sf::Texture seleceted_texture;
    seleceted_texture.loadFromFile(path + "launcher_selected.png");
    sf::Sprite selected(seleceted_texture);
    selected.setScale(1.0f, 0.5f);
    
    
    sf::Text scale_text;
    scale_text.setFont(*font);
    scale_text.setFillColor(sf::Color::Black);
    scale_text.setPosition(10.0f, 75.0f);
    scale_text.setString("Scale:");
    
    std::string scale_string = "";
    sf::Text scale_entered;
    scale_entered.setFont(*font);
    scale_entered.setFillColor(sf::Color::Black);
    scale_entered.setPosition(95.0f, 75.0f);
    
    
    sf::Text texture_text;
    texture_text.setFont(*font);
    texture_text.setFillColor(sf::Color::Black);
    texture_text.setPosition(10.0f, 150.0f);
    texture_text.setString("Texture:");
    
    std::string texture_string = "";
    sf::Text texture_entered;
    texture_entered.setFont(*font);
    texture_entered.setFillColor(sf::Color::Black);
    texture_entered.setPosition(120.0f, 150.0f);
    
    selected_text s_type = NONE;
    
       while (settings->isOpen())
       {
           // Process events
           sf::Event event;
           while (settings->pollEvent(event))
           {
               // Close window: exit
               if (event.type == sf::Event::Closed)
                   settings->close();
               
               if (event.type == sf::Event::MouseButtonReleased)
                   if (event.mouseButton.button == sf::Mouse::Left)
                   {
                       sf::Vector2i mouse_world = sf::Mouse::getPosition(*settings); //Получаем координаты мышки на экране
                       sf::Vector2f pos = settings->mapPixelToCoords(mouse_world);   //Переводим в пиксели
                       pos.y = int( pos.y / 50) * 50;
                       _print("pos.y", pos.y);
                       if ((pos.y == 50)||(pos.y == 100))
                       {
                           selected.setPosition(0, 70.0f);
                           s_type = SCALE;
                       }
                       
                       if ((pos.y == 100)||(pos.y == 150))
                       {
                           selected.setPosition(0, 145.0f);
                           s_type = TEXTURE_TYPE;
                       }
                   }
               
               if (event.type == sf::Event::TextEntered)
               {
                   switch (s_type) {
                       case SCALE:
                           if ( ((event.text.unicode > 47) && (event.text.unicode < 58)) || event.text.unicode == 46 || event.text.unicode == 8 )
                                    {
                                        if ( event.text.unicode == 8)
                                        {
                                            scale_string = scale_string.substr(0, scale_string.length() - 1 );
                                        } else
                                        {
                                            scale_string += static_cast<char>(event.text.unicode);
                                        }
                                        scale_entered.setString(scale_string);
                                        _print("scale_string", scale_string);
                                        _print("event.text.unicode",  event.text.unicode);
                                    }
                           break;
                           
                           case TEXTURE_TYPE:
                           if ( event.text.unicode < 128 )
                                    {
                                        if ( event.text.unicode == 8)
                                        {
                                            texture_string = texture_string.substr(0, texture_string.length() - 1 );
                                        } else
                                        {
                                            texture_string += static_cast<char>(event.text.unicode);
                                        }
                                        texture_entered.setString(texture_string);
                                        _print("texture_string", texture_string);
                                        _print("event.text.unicode",  event.text.unicode);
                                    }
                           break;
                           
                       default:
                           break;
                   }
               
               }
           }
           // Clear screen
           settings->clear();
           
           settings->draw(background);
           
           if (s_type)
           {
               settings->draw(selected);
           }

           settings->draw(scale_text);
           settings->draw(scale_entered);
           
           settings->draw(texture_text);
           settings->draw(texture_entered);
           
           // Update the window
           settings->display();
       }

    
    return 0;
}
