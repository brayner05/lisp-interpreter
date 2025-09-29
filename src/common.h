#ifndef LISP_COMMON_H
#define LISP_COMMON_H

#include <stdbool.h>
#include <stdint.h>

typedef struct Error {
    char *message;
    uint32_t column;
} Error;

#endif