
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <stdlib.h>

using namespace std;

#ifndef NODE_H
#define NODE_H
class Node
{
public:
    Node *left = NULL;
    Node *right = NULL;
    Node(Node *n);
    Node(string str);
    void setterFname(string a);
    string getterFname();
    void setterLname(string a);
    string getterLname();
    void setterPhone(string a);
    string getterPhone();
    void setterAddress(string a);
    string getterAddress();
    string getCatergory(int catergory);

private:
    string fname, lname, address, phone;
};

#endif // !NODE_H
