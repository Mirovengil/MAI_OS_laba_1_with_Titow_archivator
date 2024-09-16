#include "tree_by_IVAN.h"
#include "archivator_by_IVAN.h"
#include "errors_codes.h"
#include <stdio.h>

const char *directoryToCompress = "./directory_for_compression/";

int main(void)
{
	
	struct Tree *directoryTree;
	enum ErrorCodes errCode = formTreeWithDirectory(&directoryTree, directoryToCompress);
	if (errCode != OK)
	{
		printf("Error: %s", ERROR_MESSAGES[errCode]);
		return errCode;
	};
	
	printf("Директория, которую вы хотите сжать, имеет вид: \n");
	printTree(directoryTree);

	char *codedTree;
	int shift, sizeOfArray;
	codeTreeAsArrayOfBytes(directoryTree, &codedTree, &shift, &sizeOfArray);

	for (int i = 0; i < sizeOfArray; ++i)
	{
		printf("%d\t", codedTree[i]);
		if (i % 8 == 0)
			printf("\n");
	}

	deleteTree(directoryTree);
	return 0;
};
