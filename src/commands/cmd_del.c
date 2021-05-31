/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file
*/

#include "ftp.h"

void cmd_del(client_t *client, char **splitted)
{
    if (is_connected(client) == 0)
        return;
    if (splitted[1] == NULL || strcasecmp(splitted[1], "") == 0) {
        send_command(client, 501, "Syntax error in parameters or arguments.");
        return;
    }
    if (remove(splitted[1]) == 0) {
        send_command(client, 250, "Requested file action okay, completed.");
    }
    else {
        send_command(client, 550, "Requested action not taken.");
    }
}