#ifndef ERRORS_CODES_H
#define ERRORS_CODES_H

enum ErrorCodes
{
    DIRECTORY_NOT_OPENED,
    NUMBER_OF_REGISTERED_ERRORS,
    OK 
};

static const char* ERROR_MESSAGES[NUMBER_OF_REGISTERED_ERRORS] = 
{
    "Ошибка сжатия: не удалось открыть входную папку!\n",
};

#endif //ERRORS_CODES_H