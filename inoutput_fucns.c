//
// Created by leva on 14.05.2022. 20:37
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *input_string() {
    size_t size = 80;
    size_t curr = 0;
    char *buffer = malloc(size);
    while (fgets(buffer + curr, size - curr, stdin)) {
        if (strchr(buffer + curr, '\n')) {
            buffer[strcspn(buffer, "\n")] = '\0';
            return buffer;
        }

        curr = size - 1;
        size *= 2;
        char *tmp = realloc(buffer, size);
        free(buffer);
        buffer = tmp;
    }

    return buffer;
}


int input_int_check(char value_array[]) {
    for (int i = 0; i < strlen(value_array) - 1; ++i) {
        if ((value_array[i] < '0') || (value_array[i] > '9')) {
            return 1;
        }
    }
    return 0;
}


int input_int() {
    char str_array_len[5];
    fgets(str_array_len, 5, stdin);
    fflush(stdin);
    if (input_int_check(str_array_len) ||
        strlen(str_array_len) == 1) {
        return -1;
    }

    return strtol(str_array_len, NULL, 10);
}


