#ifndef ARCHIVATOR_BY_IVAN
#define ARCHIVATOR_BY_IVAN

#include "errors_codes.h"
#include "tree_by_IVAN.h"

enum ErrorCodes formTreeWithDirectory(struct Node **tree, const char *directoryName);

// кодирует дерево как массив байтов и возвращает указатель на оный массив 
char* codeTreeAsArrayOfBytes(struct Node *tree);

#endif //ARCHIVATOR_BY_IVAN
