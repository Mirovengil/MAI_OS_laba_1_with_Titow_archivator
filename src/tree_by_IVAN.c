#include "tree_by_IVAN.h"
#include <stdlib.h>
#include <string.h>

struct Node* createNewFolderNode(const char *directory_name)
{
    struct Node *newTree = malloc(sizeof(struct Node));
    
    newTree->type = FOLDER;

    newTree->data = malloc(sizeof(int));
    *((int*)newTree->data) = 0;         // предположительно -- папка пустая
    
    // копируем название по-сишному
    newTree->name = malloc(sizeof(char)*strlen(directory_name));
    strcpy(newTree->name, directory_name);

    return newTree;
};

struct Node* createNewFileNode(const char *filename)
{
    struct Node *newTree = malloc(sizeof(struct Node));

    newTree->type = FILE;
    newTree->data = NULL;    // пока не заполнено! 

    // копируем название по-сишному
    newTree->name = malloc(sizeof(char)*strlen(filename));
    strcpy(newTree->name, filename);

    return newTree; 
};

void deleteTree(struct Node* tree)
{
    // если папка -- удаляем всё содержимое как отдельные Node
    if (tree->type == FOLDER)
    {
        int numberOfObjects = *((int*)tree->data);

        tree->data = (int*)tree->data + 1;  // сдвигаем указатель на первый объект в списке
        for (int i = 0; i < numberOfObjects; ++i)
        {
            // удаляем все объекты Node в папке по очереди
            deleteTree((struct Node*)tree->data[i]);
        };

        tree->data = (int*)tree->data + 1;  // сдвигаем указатель обратно
        
        // и просто очищаем выделенную память
        free(tree->data);
        free(tree->name);

        // здесь можно было написать вместо двух free один конгениальный, но неочевидный ход:
        // tree->type = FILE;
        // тогда бы следующий if сам всё удалил. 
        // Но это уже из разряда олимпиадного программирования))
    };

    // если файл -- просто чистим содержимое
    if (tree->type == FILE)
    {
        free(tree->data);
        free(tree->name);
    };
};