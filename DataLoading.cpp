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

chess_figure* LoadFigures(chess_figure* p_figures, std::string PATH) {    //вот прям чую, что мы протупили и можно было нормально объявить
    // но хз как именно

    p_figures[0].postion.x = 100; //координата по X
    p_figures[0].postion.y  = 0;  //Координата по y
    p_figures[0].type = b_Bishop;
    p_figures[0].texture = LoadFigureTexture(b_Bishop, PATH);

    p_figures[1].postion.x = 600;
    p_figures[1].postion.y = 0;
    p_figures[1].type = b_Bishop;
    p_figures[1].texture = LoadFigureTexture(b_Bishop, PATH);


    p_figures[2].postion.x = 200;
    p_figures[2].postion.y = 0;
    p_figures[2].type = b_Night;
    p_figures[2].texture = LoadFigureTexture( b_Night, PATH);

    p_figures[3].postion.x = 500;
    p_figures[3].postion.y = 0;
    p_figures[3].type = b_Night;
    p_figures[3].texture = LoadFigureTexture( b_Night, PATH);

    p_figures[4].postion.x = 300;
    p_figures[4].postion.y = 0;
    p_figures[4].type = b_Qween;
    p_figures[4].texture = LoadFigureTexture( b_Qween, PATH);

    p_figures[5].postion.x = 400;
    p_figures[5].postion.y = 0;
    p_figures[5].type = b_King;
    p_figures[5].texture = LoadFigureTexture( b_King, PATH);

    p_figures[6].postion.x = 0;
    p_figures[6].postion.y = 0;
    p_figures[6].type = b_Rook;
    p_figures[6].texture = LoadFigureTexture( b_Rook, PATH);

    p_figures[7].postion.x = 700;
    p_figures[7].postion.y = 0;
    p_figures[7].type = b_Rook;
    p_figures[7].texture = LoadFigureTexture( b_Rook, PATH);

    // /////////

    p_figures[16].postion.x = 100; //координата по X
    p_figures[16].postion.y = 700; //Координата по y
    p_figures[16].type = w_Bishop;
    p_figures[16].texture = LoadFigureTexture(w_Bishop, PATH);

    p_figures[17].postion.x = 600;
    p_figures[17].postion.y = 700;
    p_figures[17].type = w_Bishop;
    p_figures[17].texture = LoadFigureTexture(w_Bishop, PATH);


    p_figures[18].postion.x = 200;
    p_figures[18].postion.y = 700;
    p_figures[18].type = w_Night;
    p_figures[18].texture = LoadFigureTexture( w_Night, PATH);

    p_figures[19].postion.x = 500;
    p_figures[19].postion.y = 700;
    p_figures[19].type = w_Night;
    p_figures[19].texture = LoadFigureTexture( w_Night, PATH);

    p_figures[20].postion.x = 300;
    p_figures[20].postion.y = 700;
    p_figures[20].type = w_Qween;
    p_figures[20].texture = LoadFigureTexture( w_Qween, PATH);

    p_figures[21].postion.x = 400;
    p_figures[21].postion.y = 700;
    p_figures[21].type = w_King;
    p_figures[21].texture = LoadFigureTexture( w_King, PATH);

    p_figures[22].postion.x = 0;
    p_figures[22].postion.y = 700;
    p_figures[22].type = w_Rook;
    p_figures[22].texture = LoadFigureTexture( w_Rook, PATH);

    p_figures[23].postion.x = 700;
    p_figures[23].postion.y = 700;
    p_figures[23].type = w_Rook;
    p_figures[23].texture = LoadFigureTexture( w_Rook, PATH);


    p_figures[24].postion.x = 700;
    p_figures[24].postion.y = 700;
    p_figures[24].texture = LoadFigureTexture( w_Rook, PATH);


    for (int i = 8; i < 16; i++)
    {
        p_figures[i].postion.x = (i - 8) * 100; //Объявление черных пешек
        p_figures[i].postion.y = 100;
        p_figures[i].type = b_Pawn;
        p_figures[i].texture = LoadFigureTexture(b_Pawn, PATH);

    }

    for (int i = 24; i < 32; i++)
    {
        p_figures[i].postion.x = (i - 24) * 100; //Объявление белых пешек
        p_figures[i].postion.y = 600;
        p_figures[i].type = w_Pawn;
        p_figures[i].texture = LoadFigureTexture(w_Pawn, PATH);

    }

    return p_figures;
}