#include <stdio.h>
#include <string.h>
#include "scanner/scanner.h"

#define LINE_BUFFER_SIZE 1028

/// @brief Reads a line into `line_buffer` from STDIN.
/// @param line_buffer The buffer in which to store the characters read from STDIN.
/// @return The number of characters read.
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

        if (strncmp(line_buffer, "quit", 4) == 0) 
            break;

        ScanResult result = lisp_tokenize(line_buffer, line_length);
        if (!result.success) {
            printf("%s: '%c' @ column: %u\n", result.error.message, line_buffer[result.error.column], result.error.column + 1);
            continue;
        }

        Token *token_list = result.token_list;
        for (Token *tok = token_list; tok != NULL; tok = tok->next) {
            printf("{ type: %s, length: %u, lexeme: ", token_name(tok), tok->length);

            for (size_t i = 0; i < tok->length; ++i)
                putchar(tok->start[i]);

            puts("}");
        }
    }
}