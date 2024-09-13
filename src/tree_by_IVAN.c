#include "tree_by_IVAN.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Node* createNewFolderNode(const char *directory_name)
{
    struct Node *newTree = malloc(sizeof(struct Node));
    
    newTree->type = FOLDER_NODE;

    newTree->data = malloc(sizeof(int));
    setNumberOfObjectsInFolderNode(0, newTree); // предположительно -- папка пустая
    
    // копируем название по-сишному
    newTree->name = malloc(sizeof(char)*strlen(directory_name));
    strcpy(newTree->name, directory_name);

    return newTree;
};

struct Node* createNewFileNode(const char *filename)
{
    struct Node *newTree = malloc(sizeof(struct Node));

    newTree->type = FILE_NODE;
    newTree->data = NULL;    // пока не заполнено! 

    // копируем название по-сишному
    newTree->name = malloc(sizeof(char)*strlen(filename));
    strcpy(newTree->name, filename);

    return newTree; 
};

enum ErrorCodes deleteTree(struct Node* tree)
{
    if (tree == NULL)
        return CLEAR_NULL_PTR;

    // если папка -- удаляем всё содержимое как отдельные Node
    if (tree->type == FOLDER_NODE)
    {
        int numberOfObjects = getNumberOfObjectsInFolderNode(tree);

        struct Node** treeObjects = getStartOfArrayOfObjectsInFolderNode(tree);
        for (int i = 0; i < numberOfObjects; ++i)
        {
            // удаляем все объекты Node в папке по очереди
            deleteTree(treeObjects[i]);
        };
        
        // и просто очищаем выделенную память
        free(tree->data);
        free(tree->name);

        // здесь можно было написать вместо двух free один конгениальный, но неочевидный ход:
        // tree->type = FILE_NODE;
        // тогда бы следующий if сам всё удалил. 
        // Но это уже из разряда олимпиадного программирования))
    };

    // если файл -- просто чистим содержимое
    if (tree->type == FILE_NODE)
    {
        free(tree->data);
        free(tree->name);
    };

    return OK;
};

enum ErrorCodes addNewObjectToFolderNode(struct Node* object, struct Node* folderNode)
{
    if (folderNode->type != FOLDER_NODE)
        return NODE_TYPE_ERROR;
    
    // считываем, сколько объектов уже есть
    int numberOfObjects = getNumberOfObjectsInFolderNode(folderNode);


    // увеличиваем размер массива на 1
    numberOfObjects += 1;
    folderNode->data = realloc(folderNode->data, 
        sizeof(int) + sizeof(struct Node**) * numberOfObjects);
    setNumberOfObjectsInFolderNode(numberOfObjects, folderNode);

    // записываем в конец массива указатель на новый объект
    getStartOfArrayOfObjectsInFolderNode(folderNode)[numberOfObjects - 1] = object;

    return OK;
};

// отладочная ф-я, печатает дерево, обходя оное симметрично
void printTree(struct Node *tree)
{
    _printTree(0, tree);
};

void _printTree(int numberOfTabs, struct Node *tree)
{
    for (int i = 0; i < numberOfTabs; ++i)
        printf("\t");
    
    if (tree->type == FILE_NODE)
        printf("%s (файл)\n", tree->name);
    
    if (tree->type == FOLDER_NODE)
    {
        printf("%s (папка; %d объектов)\n", tree->name, getNumberOfObjectsInFolderNode(tree));
        for (int i = 0; i < getNumberOfObjectsInFolderNode(tree); ++i)
            _printTree(numberOfTabs + 1, getStartOfArrayOfObjectsInFolderNode(tree)[i]);
    };
}

int getNumberOfObjectsInFolderNode(struct Node* folderNode)
{
    return *((int*)folderNode->data);
};

void setNumberOfObjectsInFolderNode(int number, struct Node* folderNode)
{
    *((int*)folderNode->data) = number;
};


struct Node** getStartOfArrayOfObjectsInFolderNode(struct Node* folderNode)
{
    return (int*)folderNode->data + 1;
};