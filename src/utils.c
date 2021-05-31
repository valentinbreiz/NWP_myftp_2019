/*
** EPITECH PROJECT, 2020
** FTPC
** File description:
** file
*/

#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include "include.h"

int pathexists(char *path)
{
    DIR* dir = opendir(path);

    if (dir) {
        closedir(dir);
        return (1);
    }
    else {
        closedir(dir);
        return (0);
    }
}

int isstringdigit(char *string)
{
    for (int i = 0; string[i] != 0; i++) {
        if (isdigit(string[i]) == 0)
            return (0);
    }
    return (1);
}

int print_usage(int exitcode)
{
    printf("USAGE: ./myftp port path\n");
    printf("\tport is the port number on which the server socket listens\n");
    printf("\tpath is the path to the home directory for the Anonymous user\n");
    return (exitcode);
}