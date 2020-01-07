//
//  SaveLoad.cpp
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 07.01.2020.
//

#include "SaveLoad.hpp"

bool saveGame(string PATH, chess_figure* p_figures, bool isWhiteQueue, float scale)
{
    ofstream save_file(PATH + "savedGame.txt", ios_base::trunc);
    
    unsigned short Queu = isWhiteQueue;
    save_file << Queu << std::endl;
    
    for (short i = 0; i < 33; i++) {
        
        unsigned short type = p_figures[i].type;
        unsigned int x = p_figures[i].position.x / scale;
        unsigned int y = p_figures[i].position.y / scale;
        unsigned short alive = p_figures[i].isAlive;
        
        string str = std::to_string(type) + ";" + std::to_string(x) + ";" + std::to_string(y) + ";" + std::to_string(alive);
        save_file << str << std::endl;
    }
    save_file.close();
    
    return true;
}

bool loadGame(string PATH, chess_figure* p_figures, bool& isWhiteQueue, float scale, string texture_path)
{
    string line;
    std::ifstream in(PATH + "savedGame.txt");
    
    if (in.is_open()) {
        getline(in, line);
        isWhiteQueue = std::atoi( line.c_str() ) ;
        unsigned short i = 0;
        while (getline(in, line)) {
            
            
            short index = line.find(";");
            
            string str_type = line.substr(0, index);
            figure_type type = static_cast<figure_type>( std::stoi( str_type ) );
            
            line = line.substr(index + 1, line.length() );
            
            index = line.find(";");
            string str_x = line.substr(0, index);
            int x = std::stoi( str_x );
            
            line = line.substr(index + 1, line.length() );
            
            index = line.find(";");
            string str_y = line.substr(0, index);
            int y = std::stoi( str_y );
            
            line = line.substr(index + 1, line.length() );
            
            index = line.find(";");
            string str_alive = line.substr(0, index);
            bool alive = std::stoi( str_alive ) ;
            
            p_figures[i].type = type;
            p_figures[i].texture = LoadFigureTexture(type, texture_path);
            p_figures[i].position = sf::Vector2f(x * scale, y * scale);
            p_figures[i].isAlive = alive;
            
            i++;
            
            _print("type", type);
            _print("x", x);
            _print("y", y);
            }
        }
    
    _print("isWhiteQueue", isWhiteQueue);
}
