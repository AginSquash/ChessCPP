#include <iostream>
#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window ( sf::VideoMode(900, 900), "ChessCPP");

    sf::Texture texture;
    if (!texture.loadFromFile("resources/horse.jpg"))
        return EXIT_FAILURE;

    sf::Sprite sprite(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }


            // Some CallBack functions will be here
        }

        window.clear();
        window.draw( sprite );
        window.display();
    }

    return EXIT_SUCCESS;
}