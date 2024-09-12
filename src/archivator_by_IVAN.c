#include "archivator_by_IVAN.h"
#include <stdio.h>
#include <dirent.h>		// библиотека для работы с папками 
#include <stdlib.h>
#include <string.h>

enum ErrorCodes _printAllFilesInDirectory(int numberOfTabs, const char *directoryName);

// стандартная сишная конструкция, что-то вроде параметра по умолчанию
enum ErrorCodes printAllFilesInDirectory(const char *directory)
{
	return _printAllFilesInDirectory(0, directory);
};


enum ErrorCodes _printAllFilesInDirectory(int numberOfTabs, const char *directoryName)
{
	DIR *directory;
    struct dirent *currentObject;

    directory = opendir(directoryName);
    if (!directory) {
        return DIRECTORY_NOT_OPENED;
    };

    while ( (currentObject = readdir(directory)) != NULL) {
		if (currentObject->d_name[0] == '.')
			continue;
		for (int i = 0; i <= numberOfTabs; ++i)
			printf("\t");
		printf("%s (", currentObject->d_name);
		if (currentObject->d_type == 4)
		{
			printf("папка)\n");
			
			char *subdirectoryFullName = formSubdirectoryFullName(directoryName, currentObject->d_name);
			
			enum ErrorCodes errCode = _printAllFilesInDirectory(numberOfTabs+1, subdirectoryFullName);
			if (errCode != OK)
				return errCode;
			
			free(subdirectoryFullName);
		}
		else
			printf("файл)\n");
    };

    closedir(directory);

	return OK;
};

char* formSubdirectoryFullName(const char *directoryName, const char *subdirectoryName)
{
	
	char *subdirectoryFullName = malloc(sizeof(char) * (strlen(directoryName) + strlen(subdirectoryName) + 3)); 
	
	// первая часть: полный путь до поддиректории
	strncpy(subdirectoryFullName, directoryName, strlen(directoryName));
	subdirectoryFullName[strlen(directoryName)] = '/';
	
	// вторая часть: само название поддиректории
	strncpy(subdirectoryFullName+strlen(directoryName), subdirectoryName, strlen(subdirectoryName));
	subdirectoryFullName[strlen(directoryName) + strlen(subdirectoryName)] = '/';
	subdirectoryFullName[strlen(directoryName) + strlen(subdirectoryName) + 1] = '\0';
	
	return subdirectoryFullName;
};
