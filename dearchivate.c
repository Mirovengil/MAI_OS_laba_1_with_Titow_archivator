#include "tree_by_IVAN.h"
#include "archivator_by_IVAN.h"
#include "errors_codes.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *loadedTree; int loadedTreeSizeInBytes;
	getBytesArrayFromFile("./coded_directory.dat", &loadedTree, &loadedTreeSizeInBytes);

	struct Node *decodedTree;
	int position = 0;
	decodeTreeFromArrayOfBytes(&decodedTree, loadedTree, loadedTreeSizeInBytes, &position);

	printf("Дерево после декодирования из файла: \n");
	printTree(decodedTree);

	formDirectoryWithTree(decodedTree, "./");

	deleteTree(decodedTree);
	free(loadedTree);
	return 0;
};
