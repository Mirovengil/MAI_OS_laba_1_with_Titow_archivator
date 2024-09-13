#ifndef TREE_BY_IVAN_H
#define TREE_BY_IVAN_H

#include "errors_codes.h"

enum NodeTypes
{
    FILE_NODE, 
    FOLDER_NODE,
    NUMBER_OF_NODE_TYPES
};

struct Node
{
    enum NodeTypes type;    // папка или файл?

    // в переменной data может быть два типа данных:
    // 1. если type == FILE, то в переменную data побайтово копируется содержание файла
    // 2. если type == FOLDER, то в переменную data сначала помещается переменная типа int --
    // число объектов в данной папке, а потом указатели на Node -- на объекты в папке 
    char *data; 
    char *name;         // имя файла/папки
};

struct Node* createNewFolderNode(const char *directory_name);
struct Node* createNewFileNode(const char *directory_name);

enum ErrorCodes deleteTree(struct Node* tree);
enum ErrorCodes addNewObjectToFolderNode(struct Node* object, struct Node* folderNode);

// получить/задать число объектов в папке
int getNumberOfObjectsInFolderNode(struct Node* folderNode);
void setNumberOfObjectsInFolderNode(int number, struct Node* folderNode);


// согласен, длинновато, но: получить указатель на начало списка объектов в папке
struct Node** getStartOfArrayOfObjectsInFolderNode(struct Node* folderNode);

// отладочная ф-я, печатает дерево, обходя оное симметрично
void printTree(struct Node *tree);

#endif //TREE_BY_IVAN_H