#include "tree_by_IVAN.h"
#include "archivator_by_IVAN.h"
#include "errors_codes.h"
#include <stdio.h>
#include <stdlib.h>

const int MAX_LEN_OF_STRING_NAME = 255;

int main(void)
{
	char *loadedTree; int loadedTreeSizeInBytes;

	printf("Доброе утро! Вас приветствует программа-деархиватор...");
	printf("Программа умеет работать с алгоритмом Deflate (пока нет, лол)\n");
	printf("Введите имя файла, который будет распакован.\n");
	printf("Ввод: ");

	char fileToDearchivate[MAX_LEN_OF_STRING_NAME];
	fgets(fileToDearchivate, MAX_LEN_OF_STRING_NAME, stdin);
	fileToDearchivate[strlen(fileToDearchivate) - 1] = '\0';
	getBytesArrayFromFile(fileToDearchivate, &loadedTree, &loadedTreeSizeInBytes);
	printf("Файл %s был успешно загружен из памяти!\n");


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
