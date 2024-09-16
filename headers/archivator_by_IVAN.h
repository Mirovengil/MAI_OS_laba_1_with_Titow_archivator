#ifndef ARCHIVATOR_BY_IVAN
#define ARCHIVATOR_BY_IVAN

#include "errors_codes.h"
#include "tree_by_IVAN.h"

enum ErrorCodes formTreeWithDirectory(struct Node **tree, const char *directoryName);

// представляет дерево целиком в виде массива байтов
void codeTreeAsArrayOfBytes(struct Node *tree, char **startOfArray, 
	int *shift, int *sizeOfArray);

#endif //ARCHIVATOR_BY_IVAN
