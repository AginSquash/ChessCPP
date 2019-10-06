#include <iostream>
#include <SFML/Graphics.hpp>
#include "DataLoading.h"
#include "configWorker.h"

//#define WINDOWS  //TODO Откоментируй при комплияции под винду
//#define DEBUG


#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h> 
    #define GetCurrentDir getcwd
#endif

#if defined(WINDOWS) || defined(DEBUG)
    #define PATH std::string("/")
#else
    #define PATH std::string("/.ChessCPP/")
#endif

//std::string textures_path = "";

// Создание окна
// 800*800 => 100*100 для каждой фигуры


const float scale = 0.5f;

sf::RenderWindow window ( sf::VideoMode(800 * scale, 800 * scale), "ChessCPP");

//      Небольшой экскурс:
//      предлагаю хранить в массиве не имена файлов/фигур, а соотв. им занчение ИЛИ значение типа figure_type.
//      Например вместо "bB" испольщовать 0 (ИЛИ b_Bishop), "bK" -> 1 и т.д.


int figure_to_move_index = -1; // Индекс фигуры которую мы перетаскиваем

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

            sf::Vector2f targetSize(100.0f * scale, 100.0f * scale); //целевой размер
            sprite.setScale(
                    targetSize.x / sprite.getLocalBounds().width,
                    targetSize.y / sprite.getLocalBounds().height);


            sprite.setPosition( p_figures[i].position );
            window.draw(sprite);
        }
    }
}

sf::Sprite& drawChessDesk(std::string resource_path)
{

    static sf::Texture texture;
    if (!texture.loadFromFile( resource_path + "background.png"))
    {
        printf("Loading chessdesk is fail\n");
    }
    static sf::Sprite sprite;
    sprite.setTexture(texture);


    sf::Vector2f targetSize(800.0f * scale, 800.0f * scale); //целевой размер

    sprite.setScale(
            targetSize.x / sprite.getLocalBounds().width,
            targetSize.y / sprite.getLocalBounds().height); // Подгоняет текстуру шахматной доски под размер окна.


    return sprite;
}

int GetChoisedFigure(chess_figure* p_figures, sf::Vector2f pos) //Функция находит фигуру соотв. координатам
{
    pos.x = int( (pos.x/scale) / 100) * 100 * scale;
    pos.y = int( (pos.y/scale) / 100) * 100 * scale;

    int index;
    for (int i = 0; i < 32; i++)
    {
        if (p_figures[i].position == pos )
        {
            return i;
        }
    }
    return -1;
    
}

int main() 
{

    window.setFramerateLimit(10);

    //Получаем рабочую директорию (windows/Unix-like)
    std::string path_to_workdir = GetCurrentWorkingDir();

    //Создаем ОС-зависимую переменные (пути к ресурсам)
    std::string resource_path = path_to_workdir + PATH + "resources/";

    //Функция из "configWorker.cpp". Читает конфиг и возвращает нужную папку с теустурами шахмат
    // (т.е. chess24, wikipedia и т.д.)
    std::string chess_type = getChessType( resource_path );

    //Создаем ОС-зависимую переменные (пути к текстурам)
    std::string textures_path = path_to_workdir + PATH + "resources/textures/" + chess_type + "/";

    sf::Sprite chessdesk = drawChessDesk( resource_path ); //Думаю так это будет лучше выглядеть

    sf::Texture texture;
    texture.loadFromFile( resource_path + "selected.png");
    sf::Sprite selected(texture);
    selected.setScale(scale, scale);

    chess_figure *p_figures = new chess_figure[32];
    LoadFigures(p_figures, textures_path, scale);


    bool isClicked = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mouse_world = sf::Mouse::getPosition(window); //Получаем координаты мышки на экране
                        sf::Vector2f pos = window.mapPixelToCoords(mouse_world);   //Переводим в пиксели
                        if (!isClicked) {
                            figure_to_move_index = GetChoisedFigure(p_figures, pos);
                            selected.setPosition( p_figures[figure_to_move_index].position ); // Подсвечимваем выбранную область
                            // (дебаг или оставить?)
                            isClicked = true;
                        } else {
                            pos.x = int( (pos.x/scale) / 100) * 100 * scale;
                            pos.y = int( (pos.y/scale) / 100) * 100 * scale;

                            p_figures[figure_to_move_index].position = pos;

                            isClicked = false;
                        }
                    }
                    break;

                default:
                    break;
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