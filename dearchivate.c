#include "tree.h"
#include "archivator.h"
#include "errors_codes.h"
#include "console_functions.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	enum ErrorCodes errCode;

	char fileWithCompressedDirectory[MAX_LEN_OF_STRING_NAME];
	char directoryToDearchivateIn[MAX_LEN_OF_STRING_NAME];

	char *treeCodedInBytes; int numberOfBytesTreeCodedWith;

	printf("Доброе утро! Вас приветствует программа-деархиватор...\n");
	printf("Введите имя файла, который будет распакован.\n");
	getFileOrFolderNameFromKeyboard(fileWithCompressedDirectory, "> ");

	errCode = getBytesArrayFromFile(fileWithCompressedDirectory, &treeCodedInBytes, &numberOfBytesTreeCodedWith);
	processError(errCode);
	printf("Файл \"%s\" был успешно загружен из памяти!\n", fileWithCompressedDirectory);


	struct Node *decodedTree;
	errCode = decodeTreeFromArrayOfBytes(&decodedTree, treeCodedInBytes, numberOfBytesTreeCodedWith);
	processError(errCode);

	printf("Содержимое файла: \n");
	printTree(decodedTree);

	printf("\nВведите имя директории, в которую следует распаковать файл.\n");
	getFileOrFolderNameFromKeyboard(directoryToDearchivateIn, "> ");

	errCode = formDirectoryWithTree(decodedTree, directoryToDearchivateIn);
	processError(errCode);

	printf("Файл был успешно распакован!\n");
	printf("\nБлагодарю за использование моей программы...\n");

	errCode = deleteTree(decodedTree);
	processError(errCode);

	free(treeCodedInBytes);
	return 0;
};
