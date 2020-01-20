#include "FileHandler.h"
extern int DEBUG;

FileHandler::FileHandler()
{
    this->Head = NULL;
    this->CurLoc = NULL;
    this->size = 0;
}

int FileHandler::CompareEqual(char *cmp, char *temp)
{
    char *x = cmp;
    char *y = temp;
    while (*x != '\0')
    {
        if (*x++ != *y++)
            return 0;
    }
    if (*y != '\0')
        return 0;
    return 1;
}

void FileHandler::ChangeCurLoc()
{
    CurLoc = CurLoc->next;
}

FileHandler::~FileHandler()
{
    CurLoc = Head;
    while (Head != NULL)
    {
        if (Head->fileType) // out file
            Head->outfile.close();
        else
            Head->infile.close();

        free(Head->fileName);
        Head = Head->next;
    }
}

Connector *FileHandler::AccessCurLoc()
{
    return CurLoc;
}
// Return "" if it is no files left over and file is at EOF else return the line from the file
string FileHandler::CheckCurLoc()
{
    if (!this->hasFile())
        return "";
    string str;
    if (CurLoc->infile.eof())
    {
        ChangeCurLoc();
    }
    if (CurLoc != NULL)
    {
        getline(CurLoc->infile, str);
        if (str.compare("exit") || str.compare("EXIT"))
        {
            return CheckCurLoc();
        }
        return str;
    }
    return "";
}

int FileHandler::hasFile()
{
    if (this->CurLoc == NULL)
        return 0;
    return 1;
}

void FileHandler::Output(string fileName, string outputStr)
{
    Connector *temp = this->Head;
    char *file = (char *)malloc(sizeof(fileName.length()));
    int i;
    for (i = 0; i < fileName.length(); i++)
    {
        if (fileName.at(i) != ' ')
            file[i] = fileName.at(i);
    }
    file[i] = '\0';
    while (temp != NULL)
    {
        if (CompareEqual(temp->fileName, file) && temp->fileType)
        {
            if (DEBUG)
                cout << "Outputting to file: " << outputStr << endl;
            temp->outfile << outputStr;
            return;
        }
        temp = temp->next;
    }
}

int FileHandler::AddFile(string str, int length, int out)
{
    Connector *file = new Connector(str, length, out);
    if (this->Head == NULL)
    {

        this->Head = file;
        this->CurLoc = this->Head;
        size++;
        return 0;
    }
    else
    {
        Connector *temp = this->Head;
        while (temp->next != NULL)
        {
            if (CompareEqual(temp->fileName, file->fileName)) // No file can be opened twice
                break;
            temp = temp->next;
        }
        if (!CompareEqual(temp->fileName, file->fileName))
        {
            temp->next = file;
            size++;
            return 0;
        }
    }
    file->~Connector();
    return 1;
}