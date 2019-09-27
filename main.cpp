#include <iostream>
#include <SFML/Graphics.hpp>

// Window creation
// 800*800 => 100*100 for one

#define PATH std::string("9307/chess24/")

sf::RenderWindow window ( sf::VideoMode(800, 800), "ChessCPP");

int drawFieldNEW(std::string Field[8][8])
{
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y ++)
        {

            std::string name = PATH + Field[x][y];

            sf::Texture texture;
            std::string filePath = "resources/" + name + ".png";
            texture.loadFromFile(filePath);
            sf::Sprite sprite(texture);

            sf::Vector2f targetSize(100.0f, 100.0f); //целевой размер

            sprite.setScale(
                    targetSize.x / sprite.getLocalBounds().width,
                    targetSize.y / sprite.getLocalBounds().height);

            sprite.setPosition(float(x * 100), float(y * 100));
            window.draw( sprite );

        }
    }
    return 0;

}

int drawField(sf::Sprite spriteField[8][8])
{
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y ++)
        {

                spriteField[x][y].setPosition(float(x * 100), float(y * 100));

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

sf::Sprite& drawChessDesk()
{
    static sf::Texture texture;
    if (!texture.loadFromFile("resources/chessboard_800x800.png"))
    {
        printf("Loading chessdesk is fail\n");
    }
    static sf::Sprite sprite;
    sprite.setTexture(texture);

    //TODO Вообще у нас доска уже пре-рендерная поэтому хз нужен ли следующий код
    sf::Vector2f targetSize(800.0f, 800.0f); //целевой размер

    sprite.setScale(
            targetSize.x / sprite.getLocalBounds().width,
            targetSize.y / sprite.getLocalBounds().height); // Подгоняет текстуру шахматной доски под размер окна.


    return sprite;
}



int main() {

    sf::Sprite chessdesk = drawChessDesk(); //Думаю так это будет лучше выглядеть

    std::string field[8][8]; // Поле в оперативной памяти, отвечающее за положение фигур
                             // каждая переменная имеет значение соотв. фигуре
                             // (напрмиер field[0][0] имеет значение равное "b_rook")
                             // Этот массив нужен для удобного перемещенния фигур

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

    field[0][0] = "bK";
    field[0][1] = "bB";
   /* for (int x = 0; x < 8; x++) //Цикл
    {
        for (int y = 0; y < 8; y ++)
        {
            std::string name = field[x][y];

            //name = "bK";                    //TODO После дебага имя будет не константой

            //spriteField[x][y] =  getTexture(name);

        }
    }
    printf("SpriteField loading is succefull\n");
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
        window.draw(chessdesk);
        //drawField(spriteField);
        drawFieldNEW(field);
        window.display();
    }

    return EXIT_SUCCESS;
}