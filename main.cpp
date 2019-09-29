#include <iostream>
#include <SFML/Graphics.hpp>


#define PATH std::string("resources/textures/chess24/")

// Window creation
// 800*800 => 100*100 for one
sf::RenderWindow window ( sf::VideoMode(800, 800), "ChessCPP");

//TODO  Небольшой экскурс:
//      предлагаю хранить в массиве не имена файлов/фигур, а соотв. им занчение ИЛИ значение типа figure_type.
//      Например вместо "bB" испольщовать 0 (ИЛИ b_Bishop), "bK" -> 1 и т.д.

enum figure_type {

    BLANK = -1,

    b_Bishop = 0,
    b_King   = 1,
    b_Night  = 2,
    b_Pawn   = 3,
    b_Qween  = 4,
    b_Rook   = 5,

    w_Bishop = 6,
    w_King   = 7,
    w_Night  = 8,
    w_Pawn   = 9,
    w_Qween = 10,
    w_Rook  = 11

};

struct chess_figure //Структура (надеюсь) будет использованна в дальнейшем 
{
    int x;
    int y;
    sf::Texture texture;
};

sf::Texture texture[12];
void loadTexture()
{
    texture[0].loadFromFile( PATH + "bB.png");
    texture[1].loadFromFile( PATH + "bK.png");
    texture[2].loadFromFile( PATH + "bN.png");
    texture[3].loadFromFile( PATH + "bP.png");
    texture[4].loadFromFile( PATH + "bQ.png");
    texture[5].loadFromFile( PATH + "bR.png");

    texture[6].loadFromFile( PATH + "wB.png");
    texture[7].loadFromFile( PATH + "wK.png");
    texture[8].loadFromFile( PATH + "wN.png");
    texture[9].loadFromFile( PATH + "wP.png");
    texture[10].loadFromFile( PATH + "wQ.png");
    texture[11].loadFromFile( PATH + "wR.png");
}


int drawField(figure_type Field[8][8]) // Работает лучше!
{
    for (int y = 0; y < 8; y ++)
    {
            for (int x = 0; x < 8; x++)
            {
                if (Field[y][x] >= 0) {
                    sf::Sprite sprite(texture[Field[y][x]]);

                    sf::Vector2f targetSize(100.0f, 100.0f); //целевой размер

                    sprite.setScale(
                            targetSize.x / sprite.getLocalBounds().width,
                            targetSize.y / sprite.getLocalBounds().height);

                    sprite.setPosition(float(x * 100), float(y * 100));
                    window.draw(sprite);
                }

        }
    }
    return 0;

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

    loadTexture();

    sf::Sprite chessdesk = drawChessDesk(); //Думаю так это будет лучше выглядеть


   // figure_type field[8][8] = { [0 ... 7][0 ... 7] = BLANK } ;

   figure_type  field[8][8]; // Создание массива 8*8
   for( int y = 0; y < 8; y++){    //Цикл для инициализации всех элементов массива
       for (int x = 0; x < 8; x++){
           field[y][x] = BLANK;
       }
   }
                             // Поле в оперативной памяти, отвечающее за положение фигур
                             // каждая переменная имеет значение соотв. фигуре
                             // (напрмиер field[0][0] имеет значение равное 0)
                             // Этот массив нужен для удобного перемещенния фигур
                             // TODO Поумолчанию все элменеты массива равны BLANK(-1), что сооветсвует пустому полю
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

    field[0][0] = w_Bishop;
    field[0][1] = b_Qween;

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

        drawField(field);
        window.display();
    }

    return EXIT_SUCCESS;
}