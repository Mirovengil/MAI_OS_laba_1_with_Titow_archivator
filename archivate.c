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
	char compressedDirectoryName[MAX_LEN_OF_STRING_NAME];

	printf("Доброе утро! вас приветствует программа-архиватор...\n");
	printf("Пожалуйста, введите директорию, которую хотели бы сжать.\n");

	getFileOrFolderNameFromKeyboard(directoryToCompress, "> ");
 	printf("Вас интересует директория: \"%s\"\n\n", directoryToCompress);

	struct Node *directoryTree;
	enum ErrorCodes errCode = formTreeWithDirectory(&directoryTree, directoryToCompress);
	if (errCode != OK)
	{
		printErrorMessage(errCode);
		return errCode;
	};
	
	printf("Директория была успешно распознана и считана.\n");
	printf("Директория, которую вы хотите сжать, имеет вид: \n");
	printTree(directoryTree);
	
	printf("\n\nТеперь укажите имя файла, в который должна быть сжата директория:\n");
	getFileOrFolderNameFromKeyboard(compressedDirectoryName, "> ");

	char *codedTree;
	codedTree = malloc(1);	// TODO : а нужен ли этот malloc? вообще в сишном стандарте сказано, что нет...
	int shift, sizeOfArray;	// TODO : а нужен ли shift вообще?
							// если нужен -- его надо скрыть отсюда! он чисто внутри функции codeTreeAsArrayOfBytes 
	shift = 0; sizeOfArray = 0;
	codeTreeAsArrayOfBytes(directoryTree, &codedTree, &sizeOfArray, &shift);
	saveArrayOfBytesToFile(codedTree, sizeOfArray, compressedDirectoryName);

	printf("Директория была успешно сжата!\n");
	printf("Благодарим за использование нашей программы!\n");

	deleteTree(directoryTree);
	free(codedTree);

	return 0;
};
