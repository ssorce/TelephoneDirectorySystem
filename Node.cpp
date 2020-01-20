#include "Node.h"

Node::Node(Node *n)
{
    setterFname(n->getterFname());
    setterLname(n->getterLname());
    setterAddress(n->getterAddress());
    setterPhone(n->getterPhone());
}
Node::Node(string str)
{
    string s = "";
    istringstream iss(str);
    iss >> s;
    setterFname(s);
    iss >> s;
    setterLname(s);
    iss >> s;
    setterPhone(s);
    getline(iss, s);
    setterAddress(s.substr(1));
}
void Node::setterFname(string a)
{
    this->fname = a;
}
string Node::getterFname()
{
    return this->fname;
}
void Node::setterLname(string a)
{
    this->lname = a;
}
string Node::getterLname()
{
    return this->lname;
}
void Node::setterPhone(string a)
{
    this->phone = a;
}
string Node::getterPhone()
{
    return this->phone;
}
void Node::setterAddress(string a)
{
    this->address = a;
}
string Node::getterAddress()
{
    return this->address;
}
string Node::getCatergory(int catergory)
{
    if (catergory == 0)
        return this->getterAddress();
    else if (catergory == 1)
        return this->getterPhone();
    else if (catergory == 2)
        return this->getterFname();
    else
        return this->getterLname();
}