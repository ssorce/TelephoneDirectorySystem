#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "DEBUG.h"
#ifndef CONNECTOR_H
#define CONNECTOR_H

using namespace std;
class Connector
{
public:
    bool fileType;
    char *fileName;
    ifstream infile;
    ofstream outfile;
    Connector *next = NULL;
    Connector(string str, int length, int out);
    ~Connector();
};

#endif // !FILE_H