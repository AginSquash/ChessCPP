//
//  settings.hpp
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 21.10.2019.
//

#ifndef settings_hpp
#define settings_hpp

#include <SFML/Graphics.hpp>
#include <stdio.h>

enum selected_text {
    NONE = 0,
    SCALE = 1,
    TEXTURE_TYPE = 2
};

int main_settings(sf::RenderWindow* settings, std::string path, sf::Font* font);

#endif /* settings_hpp */
