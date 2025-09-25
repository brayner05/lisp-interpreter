#include <stdio.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1028

/// @brief Reads a line into `line_buffer` from STDIN.
/// @param line_buffer The buffer in which to store the characters read from STDIN.
/// @return The nuumber of characters read.
static size_t read_line(char line_buffer[LINE_BUFFER_SIZE]) {
    size_t line_length = 0;

    while (line_length < LINE_BUFFER_SIZE) {
        int ch = getchar();
        if (ch == EOF || ch == '\n')
            break;
        line_buffer[line_length++] = ch;
    }

    return line_length;
}

int main(void) {
    char line_buffer[LINE_BUFFER_SIZE];
    while (1) {
        printf("> ");
        size_t line_length = read_line(line_buffer);

        if (strncmp(line_buffer, "quit", LINE_BUFFER_SIZE) == 0) 
            break;

        fwrite(line_buffer, sizeof(char), line_length, stdout);
        fflush(stdout);
    }
}