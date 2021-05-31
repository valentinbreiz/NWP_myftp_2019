/*
** EPITECH PROJECT, 2018
** CPE_getnextline_2018
** File description:
** CPE_getnextline_2018
*/

#include "my_str_to_word_array.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char **my_str_to_word_array(const char *str, const char *sep)
{
    char *string = strdup(str);
    char *separator = strdup(sep);
    static char *array[10];
    int index = 0;

    while (*string != 0) {
        while (*string != 0 && strchr(separator, *string)) {
            *string = 0;
            string++;
        }
        array[index++] = string;
        while (*string != 0 && !strchr(separator, *string))
            string++;
    }
    array[index] = 0;
    return array;
}