#include <iostream>
#include <SFML/Graphics.hpp>


int main() {


    // Window creation
    // 800*800 => 100*100 for one
    sf::RenderWindow window ( sf::VideoMode(800, 800), "ChessCPP");

    std::string textureArray[8][8];

    /*
     *  [0][1][2][3][4][5][6][7]
     *  [1][ ][ ][ ][ ][ ][ ][ ]
     *  [2][ ][ ][ ][ ][ ][ ][ ]
     *  [3][ ][ ][ ][ ][ ][ ][ ]
     *  [4][ ][ ][ ][ ][ ][ ][ ]
     *  [5][ ][ ][ ][ ][ ][ ][ ]
     *  [6][ ][ ][ ][ ][ ][ ][ ]
     *  [7][ ][ ][ ][ ][ ][ ][ ]
     *
     */



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
        window.display();
    }

    return EXIT_SUCCESS;
}