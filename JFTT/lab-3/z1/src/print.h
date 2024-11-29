#pragma once

typedef enum BufferStatus
{
    OK,
    NOOK
} BufferStatus_t;

// Status of the buffer, used to check whether it was overflowed
extern BufferStatus_t buffer_status;

// Write formatted string to the buffer
void write_buffer(const char* str, ...);

// Print the buffer to the standard output
void print_buffer();

// Clear the buffer and set the status back to OK
void clear_buffer();
