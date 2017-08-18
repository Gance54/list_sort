#include<log.h>

void log_print(char symbol, char *file, int line, const char *fmt, ...)
{
    printf("[%c[%s.%d]: %s \n", symbol, file, line, fmt, __VA_ARGS__);
}
