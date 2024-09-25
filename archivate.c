#include "tree_by_IVAN.h"
#include "archivator_by_IVAN.h"
#include "errors_codes.h"
#include "console_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char directoryToCompress[MAX_LEN_OF_STRING_NAME];
	char nameOfFileWithCompressedDirectory[MAX_LEN_OF_STRING_NAME];

	printf("Доброе утро! вас приветствует программа-архиватор...\n");
	printf("Пожалуйста, введите директорию, которую хотели бы сжать.\n");

	getFileOrFolderNameFromKeyboard(directoryToCompress, "> ");
 	printf("Вас интересует директория: \"%s\"\n\n", directoryToCompress);

	struct Node *directoryAsTree;
	enum ErrorCodes errCode = formTreeWithDirectory(&directoryAsTree, directoryToCompress);
	processError(errCode);
	
	printf("Директория была успешно распознана и считана.\n");
	printf("Директория, которую вы хотите сжать, имеет вид: \n");
	printTree(directoryAsTree);
	
	printf("\n\nТеперь укажите имя файла, в который должна быть сжата директория:\n");
	getFileOrFolderNameFromKeyboard(nameOfFileWithCompressedDirectory, "> ");

	char *codedTree = NULL;
	int shift, numberOfBytesInCodedTree;	
	// TODO : а нужен ли shift вообще?
	// если нужен -- его надо скрыть отсюда! он чисто внутри функции codeTreeAsArrayOfBytes 
	
	shift = 0; numberOfBytesInCodedTree = 0;
	codeTreeAsArrayOfBytes(directoryAsTree, &codedTree, &numberOfBytesInCodedTree, &shift);
	saveArrayOfBytesToFile(codedTree, numberOfBytesInCodedTree, nameOfFileWithCompressedDirectory);

	printf("Директория была успешно сжата!\n");
	printf("Благодарим за использование нашей программы!\n");

	deleteTree(directoryAsTree);
	free(codedTree);

	return 0;
};
