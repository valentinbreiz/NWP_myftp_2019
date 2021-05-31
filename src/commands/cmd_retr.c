/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cmd_retr
*/

#include "ftp.h"

void cmd_retr(client_t *client, char **splitted)
{
    if (is_connected(client) == 0)
        return;
    if (splitted[1] == NULL || strcasecmp(splitted[1], "") == 0) {
        send_command(client, 501, "Syntax error in parameters or arguments.");
        return;
    }
    if (client->mode == 0) {
        send_command(client, 150, "About to open data connection.");
        cmd_retr_pasv(client, splitted[1]);
    }
    else if (client->mode == 1) {
        send_command(client, 150, "About to open data connection.");
        cmd_retr_actv(client, splitted[1]);
    }
    else {
        send_command(client, 425, "Can't open data connection.\n");
    }
}

void cmd_retr_pasv(client_t *client, char *path)
{
    socklen_t sin_size = 0;
    char buffer[1024];
    int fd;
    int size;

    memset(buffer, 0, 1024);
    if ((client->fddata = accept(client->fddata, (struct
    sockaddr*)&client->sockdata, &sin_size)) == -1)
        return send_command(client, 425, "Can't open data connection.\n");
    if ((fd = open(path, O_RDONLY)) == -1)
        return send_command(client, 550, "Requested action not taken.");
    while ((size = read(fd, buffer, 1024)) > 0) {
        if (write(client->fddata, buffer, size) == -1)
            return send_command(client, 426,
            "Connection closed; transfer aborted.");
        memset(buffer, 0, 1024);
    }
    send_command(client, 226,"Closing data connection.");
    close(client->fddata);
}

void cmd_retr_actv(client_t *client, char *path)
{
    char buffer[1024];
    int fd;
    int size;

    memset(buffer, 0, 1024);
    if (connect(client->fddata, (struct
    sockaddr*)&client->sockdata,
    sizeof(client->sockdata)) == -1)
        return send_command(client, 425, "Can't open data connection.");
    if ((fd = open(path, O_RDONLY)) == -1)
        return send_command(client, 550, "Requested action not taken.");
    while ((size = read(fd, buffer, 1024)) > 0) {
        if (write(client->fddata, buffer, size) == -1)
            return send_command(client, 426,
            "Connection closed; transfer aborted.");
        memset(buffer, 0, 1024);
    }
    send_command(client, 226,"Closing data connection.");
    close(client->fddata);
}