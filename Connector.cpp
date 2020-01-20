#include "Connector.h"

Connector::~Connector()
{
    free(this->fileName);
}

Connector::Connector(string str, int length, int out)
{
    this->fileType = false;
    this->fileName = (char *)malloc(sizeof(length));
    int i;
    for (i = 0; i < length; i++)
    {
        if (str.at(i) != ' ')
            this->fileName[i] = str.at(i);
    }
    this->fileName[i] = '\0';

    if (out == 1)
    {
        outfile.open(this->fileName, ios::out | ios::app);
        this->fileType = true;
    }
    else
        infile.open(this->fileName);
}