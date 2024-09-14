#include "tree_by_IVAN.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Node* createNewNode(const char *directory_name, enum NodeTypes nodeType)
{
    struct Node *newTree = malloc(sizeof(struct Node));
    
    newTree->type = nodeType;

    newTree->data = NULL;
    newTree->dataSize = 0;
    
    // копируем название по-сишному
    newTree->name = malloc(sizeof(char)*strlen(directory_name));
    strcpy(newTree->name, directory_name);

    return newTree;
};

enum ErrorCodes deleteTree(struct Node* tree)
{
    if (tree == NULL)
        return CLEAR_NULL_PTR;

    // если папка -- удаляем всё содержимое как отдельные Node
    if (tree->type == FOLDER_NODE)
    {
        for (int i = 0; i < tree->dataSize; ++i)
        {
            // удаляем все объекты Node в папке по очереди
            deleteTree(((struct Node**)tree->data)[i]);
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

    // увеличиваем размер массива на 1
    folderNode->dataSize += 1;
    folderNode->data = realloc(folderNode->data, 
        sizeof(struct Node**) * folderNode->dataSize);

    // записываем в конец массива указатель на новый объект
    ((struct Node**)folderNode->data)[folderNode->dataSize - 1] = object;

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
        printf("%s (файл; %d байт)\n", tree->name, tree->dataSize);
    
    if (tree->type == FOLDER_NODE)
    {
        printf("%s (папка; %d объектов)\n", tree->name, tree->dataSize);
        for (int i = 0; i < tree->dataSize; ++i)
            _printTree(numberOfTabs + 1, ((struct Node**)tree->data)[i]);
    };
}