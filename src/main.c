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

	deleteTree(directoryTree);
	return 0;
};
