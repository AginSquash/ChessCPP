//
//  settings.cpp
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 21.10.2019.
//
#include "settings.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

//sf::RenderWindow settings (sf::VideoMode(400.0f, 400.0f), "settings" );

int main_settings(sf::RenderWindow *settings, std::string path)
{

    std::cout << "Open settings" << std::endl;
    // Start the game loop
       while (settings->isOpen())
       {
           // Process events
           sf::Event event;
           while (settings->pollEvent(event))
           {
               // Close window: exit
               if (event.type == sf::Event::Closed)
                   settings->close();
               
           }
           // Clear screen
           settings->clear();
           // Draw the sprite
           //settings->draw(sprite);

           // Update the window
           settings->display();
       }

    
    return 0;
}
