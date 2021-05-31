/*
** EPITECH PROJECT, 2020
** FTPC
** File description:
** file
*/

#ifndef FTPC_INCLUDE_H
#define FTPC_INCLUDE_H

#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int print_usage(int exitcode);
int isstringdigit(char *string);
int ftp(int port, char *path);
int pathexists(char *path);
char *get_local_ip();

#endif //FTPC_INCLUDE_H
