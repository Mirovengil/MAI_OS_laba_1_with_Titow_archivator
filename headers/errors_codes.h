#ifndef ERRORS_CODES_H
#define ERRORS_CODES_H

enum ErrorCodes
{
    DIRECTORY_NOT_OPENED,
    CLEAR_NULL_PTR,
    NODE_TYPE_ERROR,
    TREE_PTR_ERROR,
    NUMBER_OF_REGISTERED_ERRORS,
    OK
};

static const char* ERROR_MESSAGES[NUMBER_OF_REGISTERED_ERRORS] = 
{
    "Ошибка файловой системы: не удалось открыть папку!\n",
    "Ошибка с указателями: произведена попытка удалить NULL!\n",
    "Ошибка работы с Node: обращение к папке как к файлу или к файлу как к папке!\n",
    "Ошибка работы с Node: передан объект типа Node*, равный NULL!\n"
};

#endif //ERRORS_CODES_H