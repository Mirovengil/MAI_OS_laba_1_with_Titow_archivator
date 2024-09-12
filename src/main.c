#include "archivator_by_IVAN.h"
#include "errors_codes.h"

const char *directoryToCompress = "./directory_for_compression/";

int main(void)
{
	printf("Директория, которую вы хотите сжать, имеет вид: \n");
	
	enum ErrorCodes errCode = printAllFilesInDirectory(directoryToCompress);
	return 0;
};
