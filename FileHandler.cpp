#include "FileHandler.h"
extern int DEBUG;
// Set the values to NULL
FileHandler::FileHandler()
{
    this->Head = NULL;
    this->CurLoc = NULL;
    this->size = 0;
}
// Comparator
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

// Moves CurLoc to the next CurLoc
void FileHandler::ChangeCurLoc()
{
    CurLoc = CurLoc->next;
}

// Deconstructs the Files i.e. closes them and frees memory
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

//TODO: Find out if this can be private
// Accesses CurLoc
Connector *FileHandler::AccessCurLoc()
{
    return CurLoc;
}
// Return "" if it is no files left over and file is at EOF else return the line from the file
string FileHandler::CheckCurLoc()
{
    string str;
    int i;
    if (!this->hasFile())
        return "";
    if (CurLoc->infile.eof())
    {
        ChangeCurLoc();
    }
    if (CurLoc != NULL)
    {
        getline(CurLoc->infile, str);
        i = str.substr(0, 4).compare("exit");
        if (i == 0)
        {
            return CheckCurLoc();
        }
        return str;
    }
    return "";
}

// Checks if their is a file
int FileHandler::hasFile()
{
    if (this->CurLoc == NULL)
        return 0;
    return 1;
}

// Outputs to filename, so it finds it in the list and uses outputStr
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

// Finds out if their is the same file open if not adds it to the list
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