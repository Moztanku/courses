#pragma once

typedef enum BufferStatus
{
    OK,
    NOOK
} BufferStatus_t;

extern BufferStatus_t buffer_status;

void write_buffer(const char* str, ...);
void print_buffer();
void clear_buffer();
