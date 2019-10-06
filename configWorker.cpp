//
// Created by Vlad Vrublevsky on 04/10/2019.
//

#include "configWorker.h"
#include <fstream>
#include <map>
#include <string>

map<string, string> loadConfig(string PATH) {

    map<string, string> config;

    string line;
    std::ifstream in(   PATH + "config.txt");

    if (in.is_open())
    {
        while (getline(in, line))
        {
            short index = line.find("=");
            string key = line.substr(0, index);
            string value = line.substr(index + 1);
            config.insert( make_pair( key, value )  );
        }
    } else {
        cout << "Error!" << endl << "Config file is broken!" << endl; 
    }

    return config;
}
