/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file
*/

#include "ftp.h"

void cmd_pwd(client_t *client, char **splitted)
{
    char cwd[256];

    if (is_connected(client) == 0)
        return;
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("FTP : sent 257 \"/%s/\" created.\n", cwd);
        dprintf(client->fdclient, "257 \"/%s/\" created.\r\n", cwd);
    }
    else {
        send_command(client, 550, "Requested action not taken.");
    }
}