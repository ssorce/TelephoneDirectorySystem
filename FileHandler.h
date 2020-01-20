#include "Connector.h"
#include <iostream>
#include <string>
#ifndef FileHandler_H
#define FileHandler_H

using namespace std;

class FileHandler
{
private:
    int size;
    Connector *Head;
    Connector *CurLoc;
    int CompareEqual(char *cmp, char *x); // Comparing file names so that no file is opened twice
    void ChangeCurLoc();                  // Changing CurLoc to new location
    int hasFile();                        // Checks if the file is in the list

public:
    FileHandler();
    int AddFile(string str, int length, int out); // Adding File to list
    string CheckCurLoc();                         // Checks if the CurLoc is looking at a file that is EOF and changes it. Returns "" if no more files
    Connector *AccessCurLoc();
    void Output(string fileName, string outputStr); // Outputs to the file
    ~FileHandler();
};

#endif // !FileHandler_H