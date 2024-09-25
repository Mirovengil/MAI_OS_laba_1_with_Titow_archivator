#ifndef ARCHIVATOR_BY_IVAN
#define ARCHIVATOR_BY_IVAN

#include "errors_codes.h"
#include "tree_by_IVAN.h"

enum ErrorCodes formTreeWithDirectory(struct Node **tree, const char *directoryName);
enum ErrorCodes	formDirectoryWithTree(struct Node *tree, char *directory);

enum ErrorCodes	codeTreeAsArrayOfBytes(struct Node *tree, char **startOfArray, int *sizeOfArray);
enum ErrorCodes	saveArrayOfBytesToFile(char *arrayOfBytes, int length, char *fileName);
enum ErrorCodes getBytesArrayFromFile(const char *fullFilename, char **bytesArray, long *lengthOfArray);
enum ErrorCodes	decodeTreeFromArrayOfBytes(struct Node **tree, char *arrayOfBytes, int sizeOfArray);

#endif //ARCHIVATOR_BY_IVAN
