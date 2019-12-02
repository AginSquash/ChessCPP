//
// Created by Vlad Vrublevsky on 04/10/2019.
//

#ifndef CHESSCPP_CONFIGWORKER_H
#define CHESSCPP_CONFIGWORKER_H

#include <iostream>
#include <map>
#include <string>

using namespace std;

map<string, string> loadConfig(string PATH);

bool saveConfig(std::string PATH, std::map<std::string, std::string> config);

#endif // CHESSCPP_CONFIGWORKER_H
