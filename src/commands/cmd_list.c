/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file
*/

#include "ftp.h"
#include "include.h"

void cmd_list(client_t *client, char **splitted)
{
    if (is_connected(client) == 0)
        return;
    if (client->mode == 0) {
        send_command(client, 150, "About to open data connection.");
        cmd_list_pasv(client, splitted);
    }
    else if (client->mode == 1) {
        send_command(client, 150, "About to open data connection.");
        cmd_list_actv(client, splitted);
    }
    else {
        send_command(client, 425, "Can't open data connection.\n");
    }
}

void cmd_list_pasv(client_t *client, char **splitted)
{
    int	oldfd;
    socklen_t sin_size = 0;

    if ((client->fddata = accept(client->fddata, (struct
    sockaddr*)&client->sockdata, &sin_size)) == -1)
        return send_command(client, 425, "Can't open data connection.\n");
    oldfd = dup(1);
    dup2(client->fddata, 1);
    char command[1024];
    memset(command, 0, 1024);
    if (splitted[1] != NULL)
        sprintf(command, "/bin/ls -l %s", splitted[1]);
    else
        sprintf(command, "/bin/ls -l");
    system(command);
    dup2(oldfd, 1);
    send_command(client, 226, "Closing data connection.");
    close(client->fddata);
}

void cmd_list_actv(client_t *client, char **splitted)
{
    int	oldfd;
    struct sockaddr_in s;
    if (connect(client->fddata, (struct
    sockaddr*)&client->sockdata,
    sizeof(client->sockdata)) == -1)
        return send_command(client, 425, "Can't open data connection.\n");
    oldfd = dup(1);
    dup2(client->fddata, 1);
    char command[1024];
    memset(command, 0, 1024);
    if (splitted[1] != NULL)
        sprintf(command, "/bin/ls -l %s", splitted[1]);
    else
        sprintf(command, "/bin/ls -l");
    system(command);
    dup2(oldfd, 1);
    send_command(client, 226, "Closing data connection.");
    close(client->fddata);
}