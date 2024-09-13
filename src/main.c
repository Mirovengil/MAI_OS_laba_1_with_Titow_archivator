#include "archivator_by_IVAN.h"
#include "tree_by_IVAN.h"
#include "errors_codes.h"
#include <stdio.h>

const char *directoryToCompress = "./directory_for_compression/";

int main(void)
{
	
	printf("Директория, которую вы хотите сжать, имеет вид: \n");
	enum ErrorCodes errCode = printAllFilesInDirectory(directoryToCompress);
	if (errCode != OK)
	{
		printf("Error: %s", ERROR_MESSAGES[errCode]);
		return errCode;
	};
	return 0;
};
