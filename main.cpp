#include <iostream>
#include <SFML/Graphics.hpp>

// Window creation
// 800*800 => 100*100 for one
sf::RenderWindow window ( sf::VideoMode(800, 800), "ChessCPP");

int drawField(sf::Sprite spriteField[8][8])
{
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y ++)
        {
            spriteField[x][y].setPosition( float(x * 100) , float(y * 100)  );
            window.draw(spriteField[x][y]);
        }
    }
    return 0;
}

sf::Sprite& getTexture(std::string name){
    static sf::Texture texture;
    std::string filePath = "resources/" + name + ".png";
    texture.loadFromFile(filePath);
    static sf::Sprite sprite(texture);
    return sprite;
}

int main() {

    std::string field[8][8];
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

    sf::Sprite spriteField[8][8];

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y ++)
        {
            std::string name = field[x][y];

            name = "debug";                    //TODO После дебага имя будет не константой

            spriteField[x][y] =  getTexture(name);

        }
    }

    printf("SpriteField loading is succefull\n");

    sf::Texture texture;
    if (!texture.loadFromFile("resources/debug.png"))
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
        drawField(spriteField);
        window.display();
    }

    return EXIT_SUCCESS;
}