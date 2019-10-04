#include <iostream>
#include <SFML/Graphics.hpp>

//#define WINDOWS  //TODO Откоментируй при комплияции под винду
#define DEBUG


#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#if defined(WINDOWS) || defined(DEBUG)
#define PATH_to_textures std::string("/resources/textures/chess24/")
#else
#define PATH_to_textures std::string("/.projects/ChessCPP/resources/textures/chess24/")
#endif

std::string PATH = "";

// Window creation
// 800*800 => 100*100 for one
sf::RenderWindow window ( sf::VideoMode(800, 800), "ChessCPP");

//TODO  Небольшой экскурс:
//      предлагаю хранить в массиве не имена файлов/фигур, а соотв. им занчение ИЛИ значение типа figure_type.
//      Например вместо "bB" испольщовать 0 (ИЛИ b_Bishop), "bK" -> 1 и т.д.

std::string GetCurrentWorkingDir( void ) {
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    return current_working_dir;
}

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
    sf::Vector2f postion;
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

            sprite.setPosition( p_figures[i].postion );
            window.draw(sprite);
        }
    }
}

sf::Sprite& drawChessDesk()
{

    static sf::Texture texture;
    if (!texture.loadFromFile( PATH + "chessboard_800x800.png"))
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

        case BLANK:
            texture.loadFromFile( PATH + "BLANK.png" );
            break;
    }

    return texture;
}

chess_figure* LoadFigures(chess_figure* p_figures) {


    p_figures[0].postion.x = 100; //координата по X
    p_figures[0].postion.y  = 0; //Координата по y
    p_figures[0].texture = LoadFigureTexture(b_Bishop);

    p_figures[1].postion.x = 600;
    p_figures[1].postion.y = 0;
    p_figures[1].texture = LoadFigureTexture(b_Bishop);


    p_figures[2].postion.x = 200;
    p_figures[2].postion.y = 0;
    p_figures[2].texture = LoadFigureTexture( b_Night);

    p_figures[3].postion.x = 500;
    p_figures[3].postion.y = 0;
    p_figures[3].texture = LoadFigureTexture( b_Night);

    p_figures[4].postion.x = 300;
    p_figures[4].postion.y = 0;
    p_figures[4].texture = LoadFigureTexture( b_Qween);

    p_figures[5].postion.x = 400;
    p_figures[5].postion.y = 0;
    p_figures[5].texture = LoadFigureTexture( b_King);

    p_figures[6].postion.x = 0;
    p_figures[6].postion.y = 0;
    p_figures[6].texture = LoadFigureTexture( b_Rook);

    p_figures[7].postion.x = 700;
    p_figures[7].postion.y = 0;
    p_figures[7].texture = LoadFigureTexture( b_Rook);

    // /////////

    p_figures[16].postion.x = 100; //координата по X
    p_figures[16].postion.y = 700; //Координата по y
    p_figures[16].texture = LoadFigureTexture(w_Bishop);

    p_figures[17].postion.x = 600;
    p_figures[17].postion.y = 700;
    p_figures[17].texture = LoadFigureTexture(w_Bishop);


    p_figures[18].postion.x = 200;
    p_figures[18].postion.y = 700;
    p_figures[18].texture = LoadFigureTexture( w_Night);

    p_figures[19].postion.x = 500;
    p_figures[19].postion.y = 700;
    p_figures[19].texture = LoadFigureTexture( w_Night);

    p_figures[20].postion.x = 300;
    p_figures[20].postion.y = 700;
    p_figures[20].texture = LoadFigureTexture( w_Qween);

    p_figures[21].postion.x = 400;
    p_figures[21].postion.y = 700;
    p_figures[21].texture = LoadFigureTexture( w_King);

    p_figures[22].postion.x = 0;
    p_figures[22].postion.y = 700;
    p_figures[22].texture = LoadFigureTexture( w_Rook);

    p_figures[23].postion.x = 700;
    p_figures[23].postion.y = 700;
    p_figures[23].texture = LoadFigureTexture( w_Rook);


    p_figures[24].postion.x = 700;
    p_figures[24].postion.y = 700;
    p_figures[24].texture = LoadFigureTexture( w_Rook);


    for (int i = 8; i < 16; i++)
    {
        p_figures[i].postion.x = (i - 8) * 100; //Объявление черных пешек
        p_figures[i].postion.y = 100;
        p_figures[i].texture = LoadFigureTexture(b_Pawn);

    }
    
    for (int i = 24; i < 32; i++)
    {
        p_figures[i].postion.x = (i - 24) * 100; //Объявление белых пешек
        p_figures[i].postion.y = 600;
        p_figures[i].texture = LoadFigureTexture(w_Pawn);

    }

    return p_figures;
}

void GetChoisedFigure(chess_figure* p_figures, sf::Vector2f pos)
{
    int index;
    for (int i = 0; i < 16; i++)
    {
        if (p_figures[i].postion == pos )
        {
            index = i;
        }
    }

}

int main() {

        window.setFramerateLimit(15);

        PATH = GetCurrentWorkingDir() + PATH_to_textures;

        sf::Sprite chessdesk = drawChessDesk(); //Думаю так это будет лучше выглядеть


        chess_figure *p_figures = new chess_figure[32];
        LoadFigures(p_figures);



        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i mouse_world =  sf::Mouse::getPosition(window);
                    sf::Vector2f pos = window.mapPixelToCoords(mouse_world);
                    GetChoisedFigure(p_figures, pos);
                }

            }

            window.clear();
            window.draw(chessdesk);

            drawField(p_figures);
            window.display();
        }

        delete[] p_figures;
        return EXIT_SUCCESS;
}
