#include "tree_by_IVAN.h"
#include "archivator_by_IVAN.h"
#include "errors_codes.h"
#include "console_functions.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	// TODO : поизменяй имена переменных так, чтоб выглядело поадекватней
	char fileToDearchivate[MAX_LEN_OF_STRING_NAME];
	char directoryToDearchivate[MAX_LEN_OF_STRING_NAME];

	char *loadedTree; int loadedTreeSizeInBytes;

	printf("Доброе утро! Вас приветствует программа-деархиватор...\n");
	printf("Введите имя файла, который будет распакован.\n");
	getFileOrFolderNameFromKeyboard(fileToDearchivate, "> ");

	getBytesArrayFromFile(fileToDearchivate, &loadedTree, &loadedTreeSizeInBytes);
	printf("Файл %s был успешно загружен из памяти!\n");

	printf("\nВведите имя директории, в которую следует распаковать файл.\n");
	getFileOrFolderNameFromKeyboard(directoryToDearchivate, "> ");

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
