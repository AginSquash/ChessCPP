//
// Created by Vlad Vrublevsky on 04/10/2019.
//

#include "DataLoading.h"
#include <SFML/Graphics.hpp>

sf::Texture LoadFigureTexture(figure_type type, std::string PATH) ///Можно поробовать это сделать через указатели
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

chess_figure* LoadFigures(chess_figure* p_figures, std::string PATH, float scale) {    //вот прям чую, что мы протупили и можно было нормально объявить
    // но хз как именно

    p_figures[0].position.x = scale * 100; //координата по X
    p_figures[0].position.y  = 0;  //Координата по y
    p_figures[0].type = b_Bishop;
    p_figures[0].texture = LoadFigureTexture(b_Bishop, PATH);
    p_figures[0].x_move = 12;
    p_figures[0].y_move = 12; // универсальный код для слонов

    p_figures[1].position.x = scale * 600;
    p_figures[1].position.y = scale * 0;
    p_figures[1].type = b_Bishop;
    p_figures[1].texture = LoadFigureTexture(b_Bishop, PATH);
    p_figures[1].x_move = 12;
    p_figures[1].y_move = 12; // универсальный код для слонов



    p_figures[2].position.x = scale * 200;
    p_figures[2].position.y = scale * 0;
    p_figures[2].type = b_Night;
    p_figures[2].texture = LoadFigureTexture( b_Night, PATH);
    p_figures[2].x_move = 3;
    p_figures[2].y_move=1;

    p_figures[3].position.x = scale * 500;
    p_figures[3].position.y = scale * 0;
    p_figures[3].type = b_Night;
    p_figures[3].texture = LoadFigureTexture( b_Night, PATH);
    p_figures[3].x_move = 3;
    p_figures[3].y_move=1;

    p_figures[4].position.x = scale * 300;
    p_figures[4].position.y = scale * 0;
    p_figures[4].type = b_Qween;
    p_figures[4].texture = LoadFigureTexture( b_Qween, PATH);
    p_figures[4].x_move = 11;//специальный код для королевы
    p_figures[4].y_move= 11;

    p_figures[5].position.x = scale * 400;
    p_figures[5].position.y = scale * 0;
    p_figures[5].type = b_King;
    p_figures[5].texture = LoadFigureTexture( b_King, PATH);
    p_figures[5].x_move = 1;
    p_figures[5].y_move = 1;

    p_figures[6].position.x = scale * 0;
    p_figures[6].position.y = scale * 0;
    p_figures[6].type = b_Rook;
    p_figures[6].texture = LoadFigureTexture( b_Rook, PATH);

    p_figures[7].position.x = scale * 700;
    p_figures[7].position.y = scale * 0;
    p_figures[7].type = b_Rook;
    p_figures[7].texture = LoadFigureTexture( b_Rook, PATH);

    // /////////

    p_figures[16].position.x = scale * 100; //координата по X
    p_figures[16].position.y = scale * 700; //Координата по y
    p_figures[16].type = w_Bishop;
    p_figures[16].texture = LoadFigureTexture(w_Bishop, PATH);

    p_figures[17].position.x = scale * 600;
    p_figures[17].position.y = scale * 700;
    p_figures[17].type = w_Bishop;
    p_figures[17].texture = LoadFigureTexture(w_Bishop, PATH);


    p_figures[18].position.x = scale * 200;
    p_figures[18].position.y = scale * 700;
    p_figures[18].type = w_Night;
    p_figures[18].texture = LoadFigureTexture( w_Night, PATH);

    p_figures[19].position.x = scale * 500;
    p_figures[19].position.y = scale * 700;
    p_figures[19].type = w_Night;
    p_figures[19].texture = LoadFigureTexture( w_Night, PATH);

    p_figures[20].position.x = scale * 300;
    p_figures[20].position.y = scale * 700;
    p_figures[20].type = w_Qween;
    p_figures[20].texture = LoadFigureTexture( w_Qween, PATH);
    p_figures[20].x_move = 11;//специальный код для королевы
    p_figures[20].y_move= 11;

    p_figures[21].position.x = scale * 400;
    p_figures[21].position.y = scale * 700;
    p_figures[21].type = w_King;
    p_figures[21].texture = LoadFigureTexture( w_King, PATH);

    p_figures[22].position.x = scale * 0;
    p_figures[22].position.y = scale * 700;
    p_figures[22].type = w_Rook;
    p_figures[22].texture = LoadFigureTexture( w_Rook, PATH);

    p_figures[23].position.x = scale * 700;
    p_figures[23].position.y = scale * 700;
    p_figures[23].type = w_Rook;
    p_figures[23].texture = LoadFigureTexture( w_Rook, PATH);


    p_figures[24].position.x = scale * 700;
    p_figures[24].position.y = scale * 700;
    p_figures[24].texture = LoadFigureTexture( w_Rook, PATH);


    for (int i = 8; i < 16; i++)
    {
        p_figures[i].position.x = scale * (i - 8) * 100; //Объявление черных пешек
        p_figures[i].position.y = scale * 100;
        p_figures[i].type = b_Pawn;
        p_figures[i].texture = LoadFigureTexture(b_Pawn, PATH);
        p_figures[i].x_move=0;
        p_figures[i].y_move=1;

    }

    for (int i = 24; i < 32; i++)
    {
        p_figures[i].position.x = scale * (i - 24) * 100; //Объявление белых пешек
        p_figures[i].position.y = scale * 600;
        p_figures[i].type = w_Pawn;
        p_figures[i].texture = LoadFigureTexture(w_Pawn, PATH);
        p_figures[i].x_move=0;
        p_figures[i].y_move=1;

    }

    return p_figures;
}