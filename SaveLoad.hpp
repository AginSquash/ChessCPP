//
//  SaveLoad.hpp
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 07.01.2020.
//

#ifndef SaveLoad_hpp
#define SaveLoad_hpp

#include <stdio.h>
#include <map>
#include <string>
#include <fstream>

#include "types.h"

#include "debug_func.hpp"
using namespace std;

bool saveGame(string PATH, chess_figure* p_figures, bool isWhiteQueue, float scale);

bool loadGame(string PATH, chess_figure* p_figures, bool& isWhiteQueue, float& scale, string texture_path);
#endif /* SaveLoad_hpp */
