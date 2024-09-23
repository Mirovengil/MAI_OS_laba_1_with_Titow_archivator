#ifndef ARCHIVATOR_BY_IVAN
#define ARCHIVATOR_BY_IVAN

#include "errors_codes.h"
#include "tree_by_IVAN.h"

enum ErrorCodes formTreeWithDirectory(struct Node **tree, const char *directoryName);
void 			formDirectoryWithTree(struct Node *tree, char *directory);

void 			codeTreeAsArrayOfBytes(struct Node *tree, char **startOfArray, 
										int *shift, int *sizeOfArray);
void 			saveArrayOfBytesToFile(char *arrayOfBytes, int length, char *fileName);
enum ErrorCodes getBytesArrayFromFile(const char *fullFilename, char **bytesArray, long *lengthOfArray);
void 			decodeTreeFromArrayOfBytes(struct Node **tree, char *arrayOfBytes, int sizeOfArray, int *position);
char *getFolderPersonalName(const char *directoryFullName);

#endif //ARCHIVATOR_BY_IVAN
