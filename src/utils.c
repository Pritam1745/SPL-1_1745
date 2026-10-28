#include <stdio.h>
#include "../include/utils.h"

int my_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void my_strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int my_strcmp(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

void read_string(char *buffer, int max_length) {
    fgets(buffer, max_length, stdin);
    int len = my_strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

double string_to_double(const char *str) {
    double result = 0.0;
    double fraction = 1.0;
    int is_fraction = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            is_fraction = 1;
            continue;
        }
        if (!is_fraction) {
            result = result * 10.0 + (str[i] - '0');
        } else {
            fraction /= 10.0;
            result += (str[i] - '0') * fraction;
        }
    }
    return result;
}