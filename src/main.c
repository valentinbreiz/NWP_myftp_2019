/*
** EPITECH PROJECT, 2020
** FTPC
** File description:
** file
*/

#include "include.h"
#include "ftp.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc == 2) {
        if (strcmp(argv[1], "-help") == 0)
            return print_usage(0);
        else
            return print_usage(84);
    }
    if (argc > 3 || argc < 2)
        return print_usage(84);
    if (isstringdigit(argv[1]) && pathexists(argv[2]))
        return (ftp(atoi(argv[1]), argv[2]));
    return print_usage(84);
}

int ftp(int port, char *path)
{
    server_t *server = malloc(sizeof(server_t));

    printf("FTP : starting server at port %d in /%s\n", port, path);
    chdir(path);
    srand(time(NULL));
    init_ftpserver(server, port);
    printf("FTP: listening\n");
    server->clientcount = 0;
    while (1) {
        int fdclient = accept(server->fdserver,
        (struct sockaddr*)&server->_client, &server->sin_size);
        getsockname(fdclient, (struct
        sockaddr *)&server->_server, &server->sin_size);
        printf("FTP: got connection from %s port %d\n",
        inet_ntoa(server->_client.sin_addr), ntohs(server->_client.sin_port));
        receive_new_client(fdclient,
        port, server->clientcount, inet_ntoa(server->_server.sin_addr));
        server->clientcount++;
    }
}