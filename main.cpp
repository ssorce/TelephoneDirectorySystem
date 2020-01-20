
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <queue>
#include "Connector.h"
#include "Node.h"
#include "FileHandler.h"
#include "DEBUG.h"

using namespace std;
extern int DEBUG;
void FindTree(Node *hd, string str, int catergory);                                    // Finds where to add the data in the tree
void FindTree(Node *hd, Node *str, int catergory);                                     // Finds where to add the data in the tree
void TraverseTree(Node *hd);                                                           // Goes through the tree to make a singly linked list
Node *TraverseTreeHelper(Node *hd, Node *list);                                        // Makes the singly linked list
Node *OrderTree(Node *hd, int catergory);                                              // Changes the order of the tree
string Choice(string str, int *catergory);                                             // Determines the choices from the users
string PrintList(Node *list);                                                          // Does in order and makes a string of the nodes' data
void Scheduler(FileHandler *filehandler);                                              // The scheduler for the priority of tasks that need to be done to the data
void Separator(string expression, string x, FileHandler *filehandler, int *catergory); // Separators for imports
/*
    This is a directory with phone, addresses, first and last name. Accessible in different forms.
    Can add, update, and delete records. Have the ability to export to a file or stdout.
    Exits is only when exit is inputed.
*/

Node *tail = NULL; // Tail of the list
Node *head = NULL; // Head of the list
int main(int argc, char **argv)
{
    FileHandler *filehandler = new FileHandler();
    Scheduler(filehandler);
    filehandler->~FileHandler();
    return 0;
}

void Scheduler(FileHandler *filehandler)
{
    string str = "temp";
    string temp = "";
    int catergory = 3;
    while (str.compare("EXIT") != 0)
    {
        str = filehandler->CheckCurLoc();
        if (str.compare("") != 0)
        {
            if (DEBUG)
                cout << "Str is from a file: " << str << endl;
        }
        else
        {
            if (DEBUG)
                cout << "User Input" << endl;
            cout << ">> ";
            getline(cin, str);
        }
        str = Choice(str, &catergory);
        if (str.substr(0, 4).find("file") == 0)
        {
            str = str.substr(5);
            filehandler->AddFile(str, str.length(), 0);
        }
        if (str.substr(0, 6).find("import") == 0)
        {
            str = str.substr(7);
            if (str.substr(0, 4).find("file") == 0)
            {
                Separator("file", str.substr(4), filehandler, &catergory);
            }
            else if (str.substr(0, 3).find("add") == 0)
            {
                Separator("add", str.substr(3), filehandler, &catergory);
            }
        }
        if (str.substr(0, 6).find("export") == 0)
        {
            if (str.length() < 7)
            {
                str = PrintList(head);
                cout << str << endl;
            }
            else if (!filehandler->AddFile(str.substr(7), str.substr(7).length(), 1))
            {
                str = str.substr(7);
                filehandler->Output(str, PrintList(head));
            }
        }
    }
}
/*
    input: import file("text", "...") or import add("..", "....")
*/

//TODO: Needs testing
void Separator(string expression, string str, FileHandler *filehandler, int *catergory)
{
    int cur = 0;
    int content = 0; // Goes to true if at the end of the possible indexing
    int temp = 0;
    for (cur = 0; cur < str.length(); cur++)
    {
        if (str.at(cur) == '"')
        {
            content++;
            if (content % 2)
                temp = cur;
        }
        if (content > 0 && !(content % 2) && expression.compare("file"))
        {
            filehandler->AddFile(str.substr((temp + 1), cur), str.substr((temp + 1), cur).length(), 0);
            str = str.substr(cur);
            temp = 0;
        }
        else if (content > 0 && !(content % 2) && expression.compare("add"))
        {
            FindTree(head, str.substr((temp + 1), cur), *catergory);
            str = str.substr(cur);
        }
    }
}
//Changes based on the str actions and returns the proper string
string Choice(string str, int *catergory)
{
    int i;
    if (DEBUG)
    {
        cout << str << endl;
    }
    i = str.substr(0, 6).find("import");
    if (i == 0)
    {
        return str;
    }
    i = str.substr(0, 4).find("file");
    if (i == 0)
    {
        return str;
    }
    i = str.substr(0, 5).find("order");
    if (i == 0)
    {
        string s = "";
        istringstream iss(str);
        iss >> s;
        iss >> s;
        if (s.find("last") == 0)
        {
            head = OrderTree(head, 3);
            *catergory = 3;
        }
        else if (s.find("first") == 0)
        {
            head = OrderTree(head, 2);
            *catergory = 2;
        }
        else if (s.find("address") == 0)
        {
            head = OrderTree(head, 0);
            *catergory = 0;
        }
        else
        {
            head = OrderTree(head, 1);
            *catergory = 1;
        }
    }
    i = str.substr(0, 6).find("export");
    if (i == 0)
    {
        TraverseTree(head);
        return str;
    }
    i = str.find("add");
    if (i == 0)
    {
        if (head == NULL)
            head = new Node(str.substr(4));
        else
            FindTree(head, str.substr(4), *catergory);
    }
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

void TraverseTree(Node *hd)
{
    Node *list = NULL;
    head = TraverseTreeHelper(hd, list);
}

Node *OrderTree(Node *old, int catergory)
{
    old = TraverseTreeHelper(old, NULL);
    Node *hd = new Node(old);
    old = old->left;
    while (old != NULL)
    {
        FindTree(hd, old, catergory);
        old = old->left;
    }
    return hd;
}

Node *TraverseTreeHelper(Node *hd, Node *list)
{
    if (hd != NULL)
    {
        if (hd->left != NULL)
            list = TraverseTreeHelper(hd->left, list);
        if (list == NULL)
        {
            list = new Node(hd);
            tail = list;
        }
        else
        {
            tail->left = new Node(hd);
            tail = tail->left;
        }
        if (hd->right != NULL)
            list = TraverseTreeHelper(hd->right, list);
    }
    return list;
}

string PrintList(Node *hd)
{
    string returnValue = "";
    if (DEBUG)
        cout << "First\tLast\tPhone\t\tAddress" << endl;
    while (hd != NULL)
    {
        returnValue += hd->getterFname() + "\t" + hd->getterLname() + "\t\'" + hd->getterPhone() + "\'\t\'" + hd->getterAddress() + "\'\n";
        hd = hd->left;
    }
    return returnValue;
}

void FindTree(Node *hd, string str, int catergory)
{
    Node *node = new Node(str);
    int i;
    while (hd != NULL)
    {
        i = hd->getCatergory(catergory).compare(node->getCatergory(catergory));
        if (i > 0 && hd->left == NULL)
        {
            hd->left = node;
            return;
        }
        else if (i < 0 && hd->right == NULL)
        {
            hd->right = node;
            return;
        }
        else if (i > 0)
            hd = hd->left;
        else
        {
            hd = hd->right;
        }
    }
    return;
}

void FindTree(Node *hd, Node *str, int catergory)
{
    Node *node = new Node(str);
    int i;
    while (hd != NULL)
    {
        i = hd->getCatergory(catergory).compare(node->getCatergory(catergory));
        if (i > 0 && hd->left == NULL)
        {
            hd->left = node;
            return;
        }
        else if (i < 0 && hd->right == NULL)
        {
            hd->right = node;
            return;
        }
        else if (i > 0)
            hd = hd->left;
        else
        {
            hd = hd->right;
        }
    }
    return;
}