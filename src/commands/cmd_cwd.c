/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file
*/

#include "ftp.h"

void cmd_cwd(client_t *client, char **splitted)
{
    if (is_connected(client) == 0)
        return;
    if (chdir(splitted[1]) == 0) {
        send_command(client, 250, "Requested file action okay.");
    }
    else {
        send_command(client, 550, "Requested action not taken.");
    }
}