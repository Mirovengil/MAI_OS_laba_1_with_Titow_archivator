#ifndef CONSOLE_FUNCTIONS_H
#define CONSOLE_FUNCTIONS_H

#include "tree_by_IVAN.h"
#include "errors_codes.h"

void printTree(struct Node *tree);  // симметрично обходит дерево и печатает
void printErrorMessage(enum ErrorCodes code);

#endif //CONSOLE_FUNCTIONS_H