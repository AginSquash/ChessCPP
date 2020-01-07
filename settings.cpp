//
//  settings.cpp
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 21.10.2019.
//
#include "settings.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "configWorker.h"
#include "debug_func.hpp"

void isConfigChange(std::string path, std::map<std::string, std::string> config, std::string scale, std::string texture_pack)
{
    if ((config["scale"] != scale) || (config["texture_pack"] != texture_pack)) {
        config["scale"] = scale;
        config["texture_pack"] = texture_pack;
        _print("Saving...", 0);
        saveConfig(path, config);
    }
}

int main_settings(sf::RenderWindow* settings, std::string path, sf::Font* font)
{

    std::map<std::string, std::string> config = loadConfig(path);

    std::string chess_type;
    std::string scale_config;
    for (map<string, string>::iterator it = config.begin(); it != config.end(); it++) //Обработка конфига
    {
        cout << "Key: " << it->first << endl;
        cout << "Value: " << it->second << endl;

        string key = it->first;
        string value = it->second;

        if (key == "scale") {
            scale_config = value; // без перевода
        }
        if (key == "texture_pack") {
            chess_type = value;
        }
    }

    _print("Open settings", "");
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

    sf::Text scale_end;
    scale_end.setFont(*font);
    scale_end.setFillColor(sf::Color::Cyan);
    scale_end.setPosition(220.0f, 75.0f);

    std::string scale_string = scale_config;
    sf::Text scale_entered;
    scale_entered.setFont(*font);
    scale_entered.setFillColor(sf::Color::Black);
    scale_entered.setPosition(95.0f, 75.0f);

    sf::Text texture_text;
    texture_text.setFont(*font);
    texture_text.setFillColor(sf::Color::Black);
    texture_text.setPosition(10.0f, 150.0f);
    texture_text.setString("Texture:");

    std::string texture_string = chess_type;
    sf::Text texture_entered;
    texture_entered.setFont(*font);
    texture_entered.setFillColor(sf::Color::Black);
    texture_entered.setPosition(120.0f, 150.0f);

    sf::Text go;
    go.setFont(*font);
    go.setFillColor(sf::Color::Black);
    go.setCharacterSize(40);
    go.setString("GO!");
    go.setPosition(165, 300);
    sf::Vector2f button = sf::Vector2f(150, 275);

    scale_entered.setString(scale_string);
    float scale = atof(scale_string.c_str());
    scale_end.setString(std::to_string(int(800 * scale)) + ":" + std::to_string(int(900 * scale)));

    texture_entered.setString(texture_string);

    selected_text s_type = NONE;

    while (settings->isOpen()) {
        // Process events
        sf::Event event;
        while (settings->pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                isConfigChange(path, config, scale_string, texture_string);
                settings->close();
                exit(0);
            }

            if (event.type == sf::Event::MouseButtonReleased)
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse_world = sf::Mouse::getPosition(*settings); //Получаем координаты мышки на экране
                    sf::Vector2f pos = settings->mapPixelToCoords(mouse_world); //Переводим в пиксели
                    pos.y = int(pos.y / 50) * 50;
                    //_print("pos.y", pos.y);
                    if ((pos.y == 50) || (pos.y == 100)) {
                        selected.setPosition(0, 70.0f);
                        s_type = SCALE;
                    }

                    if ((pos.y == 100) || (pos.y == 150)) {
                        selected.setPosition(0, 145.0f);
                        s_type = TEXTURE_TYPE;
                    }

                    if ((pos.y >= button.y) && (pos.y <= button.y + 50)) {
                        if ((pos.x >= button.x) && (pos.x <= button.x + 100)) {
                            isConfigChange(path, config, scale_string, texture_string);
                            _print("button pressed", 0);
                            settings->close();
                        }
                    }
                }

            if (event.type == sf::Event::TextEntered) {
                switch (s_type) {
                case SCALE:
                    if (((event.text.unicode > 47) && (event.text.unicode < 58)) || event.text.unicode == 46 || event.text.unicode == 8) {
                        if (event.text.unicode == 8) {
                            scale_string = scale_string.substr(0, scale_string.length() - 1);
                        } else {
                            scale_string += static_cast<char>(event.text.unicode);
                        }
                        scale_entered.setString(scale_string);
                        float scale = atof(scale_string.c_str());
                        scale_end.setString(std::to_string(int(800 * scale)) + ":" + std::to_string(int(900 * scale)));
                        _print("scale_string", scale_string);
                        _print("event.text.unicode", int(event.text.unicode));
                    }
                    break;

                case TEXTURE_TYPE:
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 8) {
                            texture_string = texture_string.substr(0, texture_string.length() - 1);
                        } else {
                            texture_string += static_cast<char>(event.text.unicode);
                        }
                        texture_entered.setString(texture_string);
                        _print("texture_string", texture_string);
                        _print("event.text.unicode", int(event.text.unicode));
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

        if (s_type) {
            settings->draw(selected);
        }

        settings->draw(scale_text);
        settings->draw(scale_entered);
        settings->draw(scale_end);

        settings->draw(texture_text);
        settings->draw(texture_entered);

        settings->draw(go);
        // Update the window
        settings->display();
    }

    return 0;
}
