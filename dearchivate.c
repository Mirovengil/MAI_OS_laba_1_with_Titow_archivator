#include "tree_by_IVAN.h"
#include "archivator_by_IVAN.h"
#include "errors_codes.h"
#include "console_functions.h"

#include <stdio.h>
#include <stdlib.h>

const int MAX_LEN_OF_STRING_NAME = 255;

int main(void)
{
	char *loadedTree; int loadedTreeSizeInBytes;

	printf("Доброе утро! Вас приветствует программа-деархиватор...");
	printf("Введите имя файла, который будет распакован.\n");
	printf("Ввод: ");

	char fileToDearchivate[MAX_LEN_OF_STRING_NAME];
	fgets(fileToDearchivate, MAX_LEN_OF_STRING_NAME, stdin);
	fileToDearchivate[strlen(fileToDearchivate) - 1] = '\0';
	getBytesArrayFromFile(fileToDearchivate, &loadedTree, &loadedTreeSizeInBytes);
	printf("Файл %s был успешно загружен из памяти!\n");

	char directoryToDearchivate[MAX_LEN_OF_STRING_NAME];
	printf("\nВведите имя директории, в которую следует распаковать файл.\n");
	printf("Ввод: ");
	fgets(directoryToDearchivate, MAX_LEN_OF_STRING_NAME, stdin);
	directoryToDearchivate[strlen(directoryToDearchivate) - 1] = '\0';

	struct Node *decodedTree;
	int position = 0;
	decodeTreeFromArrayOfBytes(&decodedTree, loadedTree, loadedTreeSizeInBytes, &position);

	printf("Содержимое файла: \n");
	printTree(decodedTree);

	formDirectoryWithTree(decodedTree, directoryToDearchivate);

	printf("Файл был успешно распакован!\n");
	printf("\nБлагодарю за использование моей программы...\n");

	deleteTree(decodedTree);
	free(loadedTree);
	return 0;
};
