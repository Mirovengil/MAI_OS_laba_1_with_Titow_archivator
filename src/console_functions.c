#include "console_functions.h"
#include <stdio.h>

// private functions of .c file
void _printTree(int numberOfTabs, struct Node *tree);

void printTree(struct Node *tree)
{
    // т.к. в языке СИ нет параметров по умолчанию, то будет вот такая конструкция
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