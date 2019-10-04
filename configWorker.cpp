//
// Created by Vlad Vrublevsky on 04/10/2019.
//

#include "configWorker.h"
#include <fstream>
#include <iostream>

std::string getChessType(std::string PATH) {

    std::ifstream in(   PATH + "config.txt");

    std::string textures_path = "";
    if (in.is_open())
    {
        std::string conf;
        getline(in, conf);
        std::cout <<  conf << std::endl;
        textures_path += conf;
    } else {
        textures_path += "chess24";
    }

    return textures_path;
}