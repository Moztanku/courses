#include "print.h"

#include "stdarg.h"
#include "stdio.h"
#include "string.h"

#define BUFFER_SIZE 1024

BufferStatus_t buffer_status = OK;

char buffer[BUFFER_SIZE];
int buffer_index = 0;

void write_buffer(const char* str, ...)
{
    if (buffer_status == NOOK)
        return;

    va_list args;
    va_start(args, str);

    int length =
        vsnprintf(buffer + buffer_index, BUFFER_SIZE - buffer_index, str, args);

    va_end(args);

    if (length < 0)
    {
        buffer_status = NOOK;

        return;
    }

    buffer_index += length;
}

void print_buffer()
{
    buffer[buffer_index] = '\0';

    printf("%s", buffer);
}

void clear_buffer()
{
    buffer_index = 0;
    buffer_status = OK;
}
