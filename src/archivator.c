#include "archivator.h"
#include <dirent.h>		// библиотека для работы с папками 
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>		// здесь есть ф-ии работы с файлами

// приватные функции, которые не стоит выставлять в .h файл
char* _formSubdirectoryFullName(const char *directoryName, const char *subdirectoryName);
char* _formFileFullName(const char *directoryName, const char *fileName);
char* _getFolderPersonalName(const char *directoryFullName);
enum ErrorCodes _decodeTreeFromArrayOfBytes(struct Node **tree, char *arrayOfBytes, int sizeOfArray, int *position);
// конец приватных функций

const char codesOfTypesOfNodes[NUMBER_OF_NODE_TYPES] = {0, 1};
const enum NodeTypes decodedTypesOfNodes[NUMBER_OF_NODE_TYPES] = {FILE_NODE, FOLDER_NODE};

enum ErrorCodes formTreeWithDirectory(struct Node **tree, const char *directoryName)
{
	enum ErrorCodes errCode;

	// перед тем, как выделять память под дерево и начинать забивать в него директорию,
	// надо убедиться, что пользователь хороший человек и указал правильную директорию
	DIR *directory;
    struct dirent *currentObject;

    directory = opendir(directoryName);
    if (!directory) {
        return DIRECTORY_NOT_OPENED;
    };

	// создаём дерево; первая вершина, очевидно, папка
	char *nodePersonalName = _getFolderPersonalName(directoryName);
	createNewNode(tree, nodePersonalName, FOLDER_NODE);
	free(nodePersonalName);

    while ( (currentObject = readdir(directory)) != NULL) {

		// скрытые папки и файлы не рассматриваем
		if (currentObject->d_name[0] == '.')
			continue;

		if (currentObject->d_type == 4)
		{
			// добавляем в дерево FOLDER_NODE
			char *subdirectoryFullName = _formSubdirectoryFullName(directoryName, currentObject->d_name);

			struct Node *tmp;

			errCode = formTreeWithDirectory(&tmp, subdirectoryFullName);
			if (errCode != OK)
				return errCode;

			errCode = addNewObjectToFolderNode(tmp, *tree);
			if (errCode != OK)
				return errCode;

			free(subdirectoryFullName);
		}
		else
		{
			// добавляем в дерево FILE_NODE
			struct Node* fileNode;

			errCode = createNewNode(&fileNode, currentObject->d_name, FILE_NODE);
			if (errCode != OK)
				return errCode;

			errCode = addNewObjectToFolderNode(fileNode, *tree);
			if (errCode != OK)
				return errCode;

			// формируем имя файла целиком
			char *fileFullName = _formFileFullName(directoryName, currentObject->d_name);

			// считываем его содержимое
			enum ErrorCodes errCode;
			errCode = getBytesArrayFromFile(fileFullName, &fileNode->data, &fileNode->dataSize);
			if (errCode != OK)
				return errCode;
		}
    };

    closedir(directory);

	return OK;
};

char* _formSubdirectoryFullName(const char *directoryName, const char *subdirectoryName)
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

char *_getFolderPersonalName(const char *directoryFullName)
{
	int lastSymbolIndex = strlen(directoryFullName)-1;
	int firstSymbolIndex;
	
	for (firstSymbolIndex = lastSymbolIndex-1; firstSymbolIndex >= 0; --firstSymbolIndex)
	{
		if(directoryFullName[firstSymbolIndex] == '/')
		{
			break;
		}
	}	
	firstSymbolIndex += 1;

	char *folderPersonalName = malloc(sizeof(char) * (lastSymbolIndex - firstSymbolIndex + 1));
	for (int i = firstSymbolIndex; i < lastSymbolIndex; ++i)
		folderPersonalName[i - firstSymbolIndex] = directoryFullName[i];
	folderPersonalName[lastSymbolIndex - firstSymbolIndex] = '\0';

	return folderPersonalName;
};

char* _formFileFullName(const char *directoryName, const char *fileName)
{
	char *fileFullName = malloc(sizeof(char) * (strlen(directoryName) + strlen(fileName) + 2)); 
	
	// первая часть: полный путь до файла
	strncpy(fileFullName, directoryName, strlen(directoryName));
	fileFullName[strlen(directoryName)] = '/';
	
	// вторая часть: само название файла
	strncpy(fileFullName+strlen(directoryName), fileName, strlen(fileName));
	fileFullName[strlen(directoryName) + strlen(fileName)] = '\0';
	
	return fileFullName;
};

enum ErrorCodes getBytesArrayFromFile(const char *fullFilename, char **bytesArray, long *lengthOfArray)
{
	FILE *fIn;

	fIn = fopen(fullFilename, "rb");
	if (fIn == NULL)
		return FILE_NOT_OPENED;

	fseek(fIn, 0, SEEK_END);
	

	*lengthOfArray = ftell(fIn);
	rewind(fIn);

	*bytesArray = malloc(*lengthOfArray * sizeof(char));
	fread(*bytesArray, *lengthOfArray, 1, fIn);
	fclose(fIn);

	return OK;
};

// кодирует дерево как массив байтов и возвращает указатель на оный массив 
enum ErrorCodes codeTreeAsArrayOfBytes(struct Node *tree, char **startOfArray, int *sizeOfArray)
{
	if (tree == NULL)
		return TREE_PTR_ERROR;

	// основная информация об узле
	long sizeOfCodedNodeInBytes = 0;
	long sizeOfCodedNodeDataInBytes = 0;
	sizeOfCodedNodeInBytes += sizeof(char);		// тип Node: файл или папка?
	sizeOfCodedNodeInBytes += sizeof(int);		// длина имени (названия)
	sizeOfCodedNodeInBytes += strlen(tree->name) * sizeof(char);	// имя файла/папки
	sizeOfCodedNodeInBytes += sizeof(long);		// число объектов в папке / длина файла (в зависимости от типа Node)
	
	
	// для файла : надо выделить память под содержание файла
	sizeOfCodedNodeDataInBytes += (tree->type == FILE_NODE) * sizeof(char) * tree->dataSize;

	char signatureOfNode = codesOfTypesOfNodes[tree->type];
	int lengthOfNodesName = strlen(tree->name);

	long shift = *sizeOfArray;

	// выделяем память под запись текущего узла
	*sizeOfArray += sizeOfCodedNodeInBytes;
	*startOfArray = realloc(*startOfArray, *sizeOfArray + sizeOfCodedNodeDataInBytes);

	memcpy(*startOfArray + shift, &signatureOfNode, sizeof(char));
	shift += sizeof(char);
	memcpy(*startOfArray + shift, &lengthOfNodesName, sizeof(int));
	shift += sizeof(int);
	memcpy(*startOfArray + shift, tree->name, lengthOfNodesName * sizeof(char));
	shift += sizeof(char) * lengthOfNodesName;
	memcpy(*startOfArray + shift, &tree->dataSize, sizeof(long));
	shift += sizeof(long); 
	


	// дальше -- опять раздвоение логики: 
	// 1. для файла -- просто печатаем его байты подряд
	// 2. для папки -- рекурсивно печатаем её содержимое
	if (tree->type == FILE_NODE)
	{
		memcpy(*startOfArray + shift, tree->data, sizeof(char) * tree->dataSize);
		*sizeOfArray += sizeof(char) * sizeOfCodedNodeDataInBytes;
	}

	if (tree->type == FOLDER_NODE)
	{
		enum ErrorCodes errCode;
		for(int i = 0; i < tree->dataSize; ++i)
		{
			errCode = codeTreeAsArrayOfBytes(((struct Node**)tree->data)[i], startOfArray, sizeOfArray);
			if (errCode != OK)
				return errCode;
		}
	}

	return OK;
};

enum ErrorCodes saveArrayOfBytesToFile(char *arrayOfBytes, int length, char *fileName)
{
	FILE *fOut = fopen(fileName, "wb");

	if (fOut == NULL)
	{
		return FILE_NOT_OPENED;
	}

	fwrite(arrayOfBytes, sizeof(char) * length, 1, fOut);
	fclose(fOut);

	return OK;
}

// опять скрыл параметр по-сишному
enum ErrorCodes	decodeTreeFromArrayOfBytes(struct Node **tree, char *arrayOfBytes, int sizeOfArray)
{
	int position = 0;
	return _decodeTreeFromArrayOfBytes(tree, arrayOfBytes, sizeOfArray, &position);
};

enum ErrorCodes _decodeTreeFromArrayOfBytes(struct Node **tree, char *arrayOfBytes, int sizeOfArray, int *position)
{
	enum ErrorCodes errCode;

	if (tree == NULL)
		return TREE_PTR_ERROR;

	// на сколько сдвинется arrayOfBytes для следующей Node
	int shift = 0;

	char nodeType;
	nodeType = arrayOfBytes[*position];
	shift += sizeof(char);

	int lengthOfNodesName;
	memcpy(&lengthOfNodesName, arrayOfBytes + shift + *position, sizeof(int));
	shift += sizeof(int);
	
	char *nameOfNode = malloc(sizeof(char) * (lengthOfNodesName + 1));
	memcpy(nameOfNode, arrayOfBytes + shift + *position, sizeof(char) * lengthOfNodesName);
	nameOfNode[lengthOfNodesName] = '\0';	// потому что в файле имя лежит без терминального нуля, угу-ага

	shift += sizeof(char) * lengthOfNodesName;

	errCode = createNewNode(tree, nameOfNode, decodedTypesOfNodes[nodeType]);
	if (errCode != OK)
		return errCode;
	
	free(nameOfNode);

	long dataSize;
	memcpy(&dataSize, arrayOfBytes + shift + *position, sizeof(long));
	shift += sizeof(long);
	
	// сдвигаем укзаатель чтения
	*position += shift;

	if((*tree)->type == FILE_NODE)
	{
		(*tree)->dataSize = dataSize;
		(*tree)->data = malloc(sizeof(char) * (*tree)->dataSize);
		memcpy((*tree)->data, arrayOfBytes + *position, sizeof(char) * (*tree)->dataSize);
		*position += sizeof(char) * (*tree)->dataSize;
	}

	if((*tree)->type == FOLDER_NODE)
	{
		enum ErrorCodes errCode;
		for (int i = 0; i < dataSize; ++i)
		{
			struct Node *sonNode = NULL;
			errCode = _decodeTreeFromArrayOfBytes(&sonNode, arrayOfBytes, sizeOfArray, position);
			if (errCode != OK)
				return errCode;
			
			errCode = addNewObjectToFolderNode(sonNode, *tree);
			if (errCode != OK)
				return errCode;
		}
	}

	return OK;
}

enum ErrorCodes formDirectoryWithTree(struct Node *tree, char *directory)
{
	enum ErrorCodes errCode;

	if (tree == NULL)
		return TREE_PTR_ERROR;
	
	if (tree->type == FILE_NODE)
	{
		char *fileFullName = _formFileFullName(directory, tree->name);

		// воспользуюсь ранее объявленной функцией, чего бы и нет?
		errCode = saveArrayOfBytesToFile(tree->data, tree->dataSize, fileFullName);
		if (errCode != OK)
			return errCode;

		free(fileFullName);
	}

	if (tree->type == FOLDER_NODE)
	{
		char *subdirectoryName = _formSubdirectoryFullName(directory, tree->name);

		struct stat st = {0};
		if (stat(subdirectoryName, &st) != -1)
			return DIRECTORY_ALREADY_EXISTS;

		mkdir(subdirectoryName, 0700);

		enum ErrorCodes errCode;
		for (int i = 0; i < tree->dataSize; ++i)
		{
			errCode = formDirectoryWithTree(((struct Node **)(tree->data))[i], subdirectoryName);
			if (errCode != OK)
				return errCode;
		}
		free(subdirectoryName);
	}

	return OK;
};