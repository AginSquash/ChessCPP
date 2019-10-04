#include <iostream>
#include <SFML/Graphics.hpp>
#include "DataLoading.h"


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


int figure_to_move_index = -1; //Индекс фигуры которую мы перетаскиваем

std::string GetCurrentWorkingDir( void ) {  //Получение текущей директории
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    return current_working_dir;
}


struct chess_move{  //Структура для возможных ходов
    sf::Vector2f move;
};
int desk[8][8];



void possiblemove(short i , sf::Vector2f coor){ //Массив для нахождения возможных ходов
                                    //i - номер объекта с фигурой
                                    // coor - вектор с координатами
  /*  switch(i){
        case(2):
            window.draw(coor.x + 100; coor.y + 300 );
            window.draw(coor.x - 300; coor.y + 100 );
            window.draw(coor.x + 300; coor.y + 100 );
            window.draw(selected);
            break;

    }*/

}


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
    if (!texture.loadFromFile( PATH + "background.png"))
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

int GetChoisedFigure(chess_figure* p_figures, sf::Vector2f pos) //Функция находит фигуру соотв. координатам
{
    pos.x = int(pos.x / 100) * 100;
    pos.y = int(pos.y / 100) * 100;

    int index;
    for (int i = 0; i < 32; i++)
    {
        if (p_figures[i].postion == pos )
        {
            return i;
        }
    }
    return -1;
    
}

int main() {

        window.setFramerateLimit(10);

        PATH = GetCurrentWorkingDir() + PATH_to_textures;

        sf::Sprite chessdesk = drawChessDesk(); //Думаю так это будет лучше выглядеть

        sf::Texture texture;
        texture.loadFromFile( PATH + "selected.png");
        sf::Sprite selected(texture);

        chess_figure *p_figures = new chess_figure[32];
        LoadFigures(p_figures, PATH);


        bool isClicked = false;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i mouse_world = sf::Mouse::getPosition(window); //Получаем координаты мышки на экране
                    sf::Vector2f pos = window.mapPixelToCoords(mouse_world);   //Переводим в пиксели
                    if (!isClicked) {
                        figure_to_move_index = GetChoisedFigure(p_figures, pos);
                        selected.setPosition( p_figures[figure_to_move_index].postion ); // Подсвечимваем выбранную область
                                                                                         // (дебаг или оставить?)
                        isClicked = true;
                    } else
                    {
                        pos.x = int(pos.x / 100) * 100;
                        pos.y = int(pos.y / 100) * 100;

                        p_figures[figure_to_move_index].postion = pos;

                        isClicked = false;
                    }
                }

            }

            window.clear();
            window.draw(chessdesk);
            drawField(p_figures);
            if (isClicked) {
                window.draw(selected);
            }
            window.display();
        }

        delete[] p_figures;
        return EXIT_SUCCESS;
}
