/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file
*/

#include "ftp.h"

void cmd_stor(client_t *client, char **splitted)
{
    if (is_connected(client) == 0)
        return;
    if (splitted[1] == NULL || strcasecmp(splitted[1], "") == 0) {
        send_command(client, 501, "Syntax error in parameters or arguments.");
        return;
    }
    if (client->mode == 0) {
        send_command(client, 150, "About to open data connection.");
        cmd_stor_pasv(client, splitted[1]);
    }
    else if (client->mode == 1) {
        send_command(client, 150, "About to open data connection.");
        cmd_stor_actv(client, splitted[1]);
    }
    else {
        send_command(client, 425, "Can't open data connection.\n");
    }
}

void cmd_stor_pasv(client_t *client, char *path)
{
    socklen_t sin_size = 0;
    char buffer[1024];
    int fd;
    int size;
    memset(buffer, 0, 1024);
    if ((client->fddata = accept(client->fddata, (struct
    sockaddr*)&client->sockdata, &sin_size)) == -1)
        return send_command(client, 425, "Can't open data connection.\n");
    if ((fd = creat(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
        return send_command(client, 550, "Requested action not taken.");
    while ((size = read(client->fddata, buffer, 1024)) > 0) {
        if (write(fd, buffer, size) == -1)
            return send_command(client, 550, "Requested action not taken.");
        memset(buffer, 0, 1024);
    }
    if (size == -1)
        return send_command(client, 426,"Connection closed.");
    send_command(client, 226, "Closing data connection.");
    close(client->fddata);
}

void cmd_stor_actv(client_t *client, char *path)
{
    char buffer[1024];
    int fd;
    int size;
    memset(buffer, 0, 1024);
    if (connect(client->fddata, (struct
    sockaddr*)&client->sockdata,
    sizeof(client->sockdata)) == -1)
        return send_command(client, 425, "Can't open data connection.\n");
    if ((fd = creat(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
        return send_command(client, 550, "Requested action not taken.");
    while ((size = read(client->fddata, buffer, 1024)) > 0) {
        if (write(fd, buffer, size) == -1)
            return send_command(client, 550, "Requested action not taken.");
        memset(buffer, 0, 1024);
    }
    if (size == -1)
        return send_command(client, 426,"Connection closed.");
    send_command(client, 226, "Closing data connection.");
    close(client->fddata);
}