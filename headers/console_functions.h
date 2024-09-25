#ifndef CONSOLE_FUNCTIONS_H
#define CONSOLE_FUNCTIONS_H

#include "tree_by_IVAN.h"
#include "errors_codes.h"

static const int MAX_LEN_OF_STRING_NAME = 255;

void printTree(struct Node *tree);  // симметрично обходит дерево и печатает
void printErrorMessage(enum ErrorCodes code);
void getFileOrFolderNameFromKeyboard(char *result, char *textOfPromt);

#endif //CONSOLE_FUNCTIONS_H