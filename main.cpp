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
    b_Night  = 2, //Конь
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
    bool isAlive = true;
};


void drawField(chess_figure* p_figures)
{
    for (int i = 0; i < 32; i++)
    {
        if ( p_figures[i].isAlive ) {
            sf::Sprite sprite(p_figures[i].texture);

            sf::Vector2f targetSize(100.0f, 100.0f); //целевой размер
            sprite.setScale(
                    targetSize.x / sprite.getLocalBounds().width,
                    targetSize.y / sprite.getLocalBounds().height);

            sprite.setPosition(p_figures[i].x * 100, p_figures[i].y * 100);
            window.draw(sprite);
        }
    }
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

sf::Texture LoadFigureTexture(figure_type type) ///Можно поробовать это сделать через указатели
{
    sf::Texture texture;
    switch (type)
    {
        case b_Bishop:
            texture.loadFromFile( PATH + "bB.png" );
            break;
        case b_King:
            texture.loadFromFile( PATH + "bK.png" );
            break;
        case b_Night:
            texture.loadFromFile( PATH + "bN.png" );
            break;
        case b_Pawn:
            texture.loadFromFile( PATH + "bP.png" );
            break;
        case b_Qween:
            texture.loadFromFile( PATH + "bQ.png" );
            break;
        case b_Rook:
            texture.loadFromFile( PATH + "bR.png" );
            break;


        case w_Bishop:
            texture.loadFromFile( PATH + "wB.png" );
            break;
        case w_King:
            texture.loadFromFile( PATH + "wK.png" );
            break;
        case w_Night:
            texture.loadFromFile( PATH + "wN.png" );
            break;
        case w_Pawn:
            texture.loadFromFile( PATH + "wP.png" );
            break;
        case w_Qween:
            texture.loadFromFile( PATH + "wQ.png" );
            break;
        case w_Rook:
            texture.loadFromFile( PATH + "wR.png" );
            break;
    }

    return texture;
}

chess_figure* LoadFigures(chess_figure* p_figures) {


    p_figures[0].x = 1; //координата по X
    p_figures[0].y = 0; //Координата по y
    p_figures[0].texture = LoadFigureTexture(b_Bishop);

    p_figures[1].x = 6;
    p_figures[1].y = 0;
    p_figures[1].texture = LoadFigureTexture(b_Bishop);


    p_figures[2].x = 2;
    p_figures[2].y = 0;
    p_figures[2].texture = LoadFigureTexture( b_Night);

    for (int i = 8; i < 16; i++)
    {
        p_figures[i].x = i - 8;
        p_figures[i].y = 1;
        p_figures[i].texture = LoadFigureTexture(b_Pawn);
    }

}

void LEGACYCODE()
{
    /*
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
*/


    /*
    // figure_type field[8][8] = { [0 ... 7][0 ... 7] = BLANK } ;

    figure_type field[8][8]; // Создание массива 8*8
    for (int y = 0; y < 8; y++) {    //Цикл для инициализации всех элементов массива
        for (int x = 0; x < 8; x++) {
            field[y][x] = BLANK; //перепутанны y и x, но если поменять, то все может пойти по пизде
        }
    }
    // Поле в оперативной памяти, отвечающее за положение фигур
    // каждая переменная имеет значение соотв. фигуре
    // (напрмиер field[0][0] имеет значение равное 0)
    // Этот массив нужен для удобного перемещенния фигур
    // TODO Поумолчанию все элменеты массива равны BLANK(-1), что сооветсвует пустому полю

    */


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


    /*  field[0][0] = b_Rook;
      field[0][1] = b_Night;
      field[0][2] = b_Bishop;
      field[0][3] = b_King;
      field[0][4] = b_Qween;
      field[0][5] = b_Bishop;
      field[0][6] = b_Night;
      field[0][7] = b_Rook;

      for(int y = 0; y<8;y++)
          field[1][y] = b_Pawn;
      field[7][0] = w_Rook;
      field[7][1] = w_Night;
      field[7][2] = w_Bishop;
      field[7][3] = w_Qween;
      field[7][4] = w_King;
      field[7][5] = w_Bishop;
      field[7][6] = w_Night;
      field[7][7] = w_Rook;
      for(int y = 0; y<8;y++)
          field[6][y] = w_Pawn;*/



    /*
//Объявляем черные фигуры
//------------------------------------------------------------------
chess_figure black_bishop1; //объявление переменной фигуры
black_bishop1.x = 0; //координата по X
black_bishop1.y = 2; //Координата по y
field[black_bishop1.x][black_bishop1.y] = b_Bishop; //Вкидывем фигуру на шахматную доску
chess_figure black_bishop2;
black_bishop2.x = 0;
black_bishop2.y = 5;
field[black_bishop2.x][black_bishop2.y] = b_Bishop;
chess_figure black_king;
black_king.x = 0;
black_king.y = 3;
field[black_king.x][black_king.y] = b_King;
chess_figure black_night1;
black_night1.x = 0;
black_night1.y = 1;
field[black_night1.x][black_night1.y] = b_Night;
chess_figure black_night2;
black_night2.x = 0;
black_night2.y = 6;
field[black_night2.x][black_night2.y] = b_Night;
chess_figure black_queen;
black_queen.x = 0;
black_queen.y = 4;
field[black_queen.x][black_queen.y] = b_Qween;
chess_figure black_rook1;
black_rook1.x = 0;
black_rook1.y = 0;
field[black_rook1.x][black_rook1.y] = b_Rook;
chess_figure black_rook2;
black_rook2.x = 0;
black_rook2.y = 7;
field[black_rook2.x][black_rook2.y] = b_Rook;
//---------------------------------------------------------------------------//
//Объявление черных пешек
//Посчитал создание отдельной переменной под каждую
//пешку оптимальным решением, ибо так будет легче
//убирать их с поля во время игры
chess_figure black_pawn0;
black_pawn0.x = 1;
black_pawn0.y = 0;
field[black_pawn0.x][black_pawn0.y] = b_Pawn;
chess_figure black_pawn1; //Парные фигуры пронумерованны слева направо
black_pawn1.x = 1;    //Фигура, которая ближе к левому краю имеет индекс '1'
black_pawn1.y = 1;
field[black_pawn1.x][black_pawn1.y] = b_Pawn;
chess_figure black_pawn2;
black_pawn2.x = 1;
black_pawn2.y = 2;
field[black_pawn2.x][black_pawn2.y] = b_Pawn;
chess_figure black_pawn3;
black_pawn3.x = 1;
black_pawn3.y = 3;
field[black_pawn3.x][black_pawn3.y] = b_Pawn;
chess_figure black_pawn4;
black_pawn4.x = 1;
black_pawn4.y = 4;
field[black_pawn4.x][black_pawn4.y] = b_Pawn;
chess_figure black_pawn5;
black_pawn5.x = 1;
black_pawn5.y = 5;
field[black_pawn5.x][black_pawn5.y] = b_Pawn;
chess_figure black_pawn6;
black_pawn6.x = 1;
black_pawn6.y = 6;
field[black_pawn6.x][black_pawn6.y] = b_Pawn;
chess_figure black_pawn7;
black_pawn7.x = 1;
black_pawn7.y = 7;
field[black_pawn7.x][black_pawn7.y] = b_Pawn;
//---------------------------------------------------------------------------//



//Объявляем белые  фигуры
//------------------------------------------------------------------
chess_figure white_bishop1;
white_bishop1.x = 7;
white_bishop1.y = 2;
field[white_bishop1.x][white_bishop1.y] = w_Bishop;
chess_figure white_bishop2;
white_bishop2.x = 7;
white_bishop2.y = 5;
field[white_bishop2.x][white_bishop2.y] = w_Bishop;
chess_figure white_king;
white_king.x = 7;
white_king.y = 3;
field[white_king.x][white_king.y] = w_King;
chess_figure white_night1;
white_night1.x = 7;
white_night1.y = 1;
field[white_night1.x][white_night1.y] = w_Night;
chess_figure white_night2;
white_night2.x = 7;
white_night2.y = 6;
field[white_night2.x][white_night2.y] = w_Night;
chess_figure white_queen;
white_queen.x = 7;
white_queen.y = 4;
field[white_queen.x][white_queen.y] = w_Qween;
chess_figure white_rook1;
white_rook1.x = 7;
white_rook1.y = 0;
field[white_rook1.x][white_rook1.y] = w_Rook;
chess_figure white_rook2;
white_rook2.x = 7;
white_rook2.y = 7;
field[white_rook2.x][white_rook2.y] = w_Rook;

//---------------------------------------------------------------------------//
//Объявление белых пешек
chess_figure white_pawn0;
white_pawn0.x = 6;
white_pawn0.y = 0;
field[white_pawn0.x][white_pawn0.y] = w_Pawn;
chess_figure white_pawn1;
white_pawn1.x = 6;
white_pawn1.y = 1;
field[white_pawn1.x][white_pawn1.y] = w_Pawn;
chess_figure white_pawn2;
white_pawn2.x = 6;
white_pawn2.y = 2;
field[white_pawn2.x][white_pawn2.y] = w_Pawn;
chess_figure white_pawn3;
white_pawn3.x = 6;
white_pawn3.y = 3;
field[white_pawn3.x][white_pawn3.y] = w_Pawn;
chess_figure white_pawn4;
white_pawn4.x = 6;
white_pawn4.y = 4;
field[white_pawn4.x][white_pawn4.y] = w_Pawn;
chess_figure white_pawn5;
white_pawn5.x = 6;
white_pawn5.y = 5;
field[white_pawn5.x][white_pawn5.y] = w_Pawn;
chess_figure white_pawn6;
white_pawn6.x = 6;
white_pawn6.y = 6;
field[white_pawn6.x][white_pawn6.y] = w_Pawn;
chess_figure white_pawn7;
white_pawn7.x = 6;
white_pawn7.y = 7;
field[white_pawn7.x][white_pawn7.y] = w_Pawn;

//---------------------------------------------------------------------------//

*/


    /*
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
    */
}

int main() {

        sf::Sprite chessdesk = drawChessDesk(); //Думаю так это будет лучше выглядеть


        chess_figure *p_figures = new chess_figure[32];
        LoadFigures(p_figures);



        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();


                }


                // Some CallBack functions will be here
            }

            window.clear();
            window.draw(chessdesk);

            drawField(p_figures);
            window.display();
        }

        delete[] p_figures;
        return EXIT_SUCCESS;
}
