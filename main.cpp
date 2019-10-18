#include <iostream>
#include <SFML/Graphics.hpp>
#include "DataLoading.h"
#include "configWorker.h"
#include <fstream>

#define WINDOWS  //TODO Откоментируй при комплияции под винду
#define DEBUG


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


float scale = 0.5f;
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




//int desk[8][8]; остатки какой то более развитой цивилизации.





void inputInSave(int IndexFigure,sf::Vector2f pos, int FieldIndex, ofstream *ChessMoves){
    *ChessMoves <<"Figure " << IndexFigure << "\t"<< "x ="<<pos.x<<"\t"<<"y="<<pos.y<<"\n";
    if (FieldIndex!=0)
        *ChessMoves <<"Figure "<<FieldIndex<<" is die \n";


};


void drawField(chess_figure* p_figures,sf::RenderWindow *window)
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
            window->draw(sprite);
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

int GetFigureByPosition(chess_figure* p_figures, sf::Vector2f pos) //Функция находит фигуру соотв. координатам
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
    //Получаем рабочую директорию (windows/Unix-like)
    std::string path_to_workdir = GetCurrentWorkingDir();

    //Создаем ОС-зависимую переменные (пути к ресурсам)
    std::string resource_path = path_to_workdir + PATH + "resources/";

    ofstream ChessMoves( resource_path + "/Save.txt", ios_base::trunc); // Связываем класс с файлом и чистим его. Пока это тестовый файл, потом поменяем.



    map<string, string> config = loadConfig( resource_path );   // Подгружаем конфиг

    std::string chess_type;
    for ( map<string, string> :: iterator it = config.begin(); it != config.end(); it++ )   //Обработка конфига
    {
        cout << "Key: " << it->first << endl;
        cout << "Value: " << it->second << endl;

        string key = it->first;
        string value = it->second;

        if (key == "scale")
        {
            scale = atof(value.c_str());    // Перевод стринг в флоат
        }
        if (key == "texture_pack")
        {
            chess_type = value;
        }
    }
    
    sf::RenderWindow window ( sf::VideoMode(800 * scale, 900 * scale), "ChessCPP" );

    window.setFramerateLimit(10);

    //Функция из "configWorker.cpp". Читает конфиг и возвращает нужную папку с теустурами шахмат
    // (т.е. chess24, wikipedia и т.д.)
    //std::string chess_type = getChessType( resource_path );

    //Создаем ОС-зависимую переменные (пути к текстурам)
    std::string textures_path = path_to_workdir + PATH + "resources/textures/" + chess_type + "/";

    sf::Sprite chessdesk = drawChessDesk( resource_path ); //Думаю так это будет лучше выглядеть

    sf::Texture backBar_texture;
    backBar_texture.loadFromFile(resource_path + "backbar.png");
    sf::Sprite backBar(backBar_texture);
    backBar.setScale(scale, scale);
    backBar.setPosition(0.0f, 800.0f * scale);

    sf::Texture selected_texture;
    selected_texture.loadFromFile( resource_path + "selected.png");
    sf::Sprite selected(selected_texture);
    selected.setScale(scale, scale);

    chess_figure *p_figures = new chess_figure[32];
    LoadFigures(p_figures, textures_path, scale);


    bool isClicked = false; // Перемнная, которая хранит состояние мышки. Если false - то это "первый" клик.
                            // Если true - то это "второй" клик, а значит нужно передвинуть фигуру выбранную на первом клике
                            // в(???) координаты второго клика

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:         //Если закрываем окно
                    window.close();
                    break;
                
                case sf::Event::MouseButtonReleased:      //Если нажимем кнопку на мыш(и)
                    if (event.mouseButton.button == sf::Mouse::Left)  
                    {
                        sf::Vector2i mouse_world = sf::Mouse::getPosition(window); //Получаем координаты мышки на экране
                        sf::Vector2f pos = window.mapPixelToCoords(mouse_world);   //Переводим в пиксели
                        if (!isClicked) {       //Если это "первый" клик
                            figure_to_move_index = GetFigureByPosition(p_figures, pos);
                            selected.setPosition( p_figures[figure_to_move_index].position ); // Подсвечимваем выбранную область
                            // (дебаг или оставить?)
                            isClicked = true;
                            
                        } else {

                            if (figure_to_move_index != -1) {     // Если мы до этого выбрали пустую область - не стоит что-либо делать

                                pos.x = int( (pos.x/scale) / 100) * 100 * scale;
                                pos.y = int( (pos.y/scale) / 100) * 100 * scale;

                                int field_index = GetFigureByPosition( p_figures= p_figures, pos= pos);     // Получаем фигуру по координатам нажатия
                                if ( field_index == -1 )                                // Если GetFigureByPosition возвращает -1, значит мы нажимаем на 
                                                                                        //      пустую клетку
                                {
                                p_figures[figure_to_move_index].position = pos;
                                    inputInSave(figure_to_move_index, pos, 0, &ChessMoves);

                                } else {     

                                    if ( (field_index < 16 ) && (figure_to_move_index >= 16) ) // Значит field_index белая, а figure_to_move_index - черная
                                    {                                                          // поэтому мы убираем field_index, а на ее место 
                                        p_figures[field_index].isAlive = false;                // ставим figure_to_move_index
                                        p_figures[field_index].position = sf::Vector2f( 1100.0f * scale, 1100.0f * scale); // Переносим за карту
                                        p_figures[figure_to_move_index].position = pos;
                                        inputInSave(figure_to_move_index,pos,field_index, &ChessMoves);

                                    } else if ( (field_index >= 16) && (figure_to_move_index < 16) )// Та же функция что и выше, но при условии
                                    {                                                            // что field_index черная, а figure_to_move_index - белая
                                        p_figures[field_index].isAlive = false;  
                                        p_figures[field_index].position = sf::Vector2f( 1100.0f * scale, 1100.0f * scale);          
                                        p_figures[figure_to_move_index].position = pos;
                                        inputInSave(figure_to_move_index,pos,field_index, &ChessMoves);

                                    } else if(field_index != figure_to_move_index)//Этот if фиксит вывод надписи, когда несколько раз жмякаешь на одну фигуру
                                        std::cout << "This position is taken by an allied figure." << std::endl;

                                    
                                }
                            }
                        
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
        window.draw(backBar);
        drawField(p_figures, &window);
        if (isClicked) {
            window.draw(selected);
        }
        window.display();
    }

    delete[] p_figures;
    return EXIT_SUCCESS;
}