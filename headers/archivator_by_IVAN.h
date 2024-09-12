#ifndef ARCHIVATOR_BY_IVAN
#define ARCHIVATOR_BY_IVAN

#include "errors_codes.h"

enum ErrorCodes printAllFilesInDirectory(const char *directory);
char* formSubdirectoryFullName(const char *directoryName, const char *subdirectoryName);

#endif //ARCHIVATOR_BY_IVAN
