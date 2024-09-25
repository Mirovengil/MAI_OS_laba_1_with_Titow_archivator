#include "tree_by_IVAN.h"
#include "archivator_by_IVAN.h"
#include "errors_codes.h"
#include "console_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_LEN_OF_STRING_NAME = 255;

int main(void)
{
	char directoryToCompress[MAX_LEN_OF_STRING_NAME];
	char compressedDirectoryName[MAX_LEN_OF_STRING_NAME];

	printf("Доброе утро! вас приветствует программа-архиватор...\n");
	printf("Пожалуйста, введите директорию, которую хотели бы сжать.\n");
	printf("Директория: ");
	fgets(directoryToCompress, MAX_LEN_OF_STRING_NAME, stdin);
	
	// особенности национального ввода с клавиатуры
	directoryToCompress[strlen(directoryToCompress)-1] = '\0';
 	printf("Вас интересует директория: \"%s\"\n", directoryToCompress);

	struct Node *directoryTree;
	enum ErrorCodes errCode = formTreeWithDirectory(&directoryTree, directoryToCompress);
	if (errCode != OK)
	{
		printf("Error: %s", ERROR_MESSAGES[errCode]);
		return errCode;
	};
	
	printf("Директория была успешно распознана и считана.\n");
	printf("Директория, которую вы хотите сжать, имеет вид: \n");
	printTree(directoryTree);
	
	printf("\nТеперь укажите имя файла, в который должна быть сжата директория:\n");
	printf("Имя файла: ");
	fgets(compressedDirectoryName, MAX_LEN_OF_STRING_NAME, stdin);
	compressedDirectoryName[strlen(compressedDirectoryName) - 1] = '\0'; // затираю перенос строки, ага

	char *codedTree;
	codedTree = malloc(1);
	int shift, sizeOfArray;	// TODO : а нужен ли shift вообще?
							// если нужен -- его надо скрыть отсюда! он чисто внутри функции codeTreeAsArrayOfBytes 
	shift = 0; sizeOfArray = 0;
	codeTreeAsArrayOfBytes(directoryTree, &codedTree, &sizeOfArray, &shift);
	saveArrayOfBytesToFile(codedTree, sizeOfArray, compressedDirectoryName);
	
	deleteTree(directoryTree);
	free(codedTree);

	return 0;
};
