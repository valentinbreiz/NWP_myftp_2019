/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file
*/

#include "ftp.h"

void cmd_rmd(client_t *client, char **splitted)
{
    if (is_connected(client) == 0)
        return;
    if (rmdir(splitted[1]) == 0) {
        send_command(client, 200, "Command okay.");
    }
    else {
        send_command(client, 550, "Requested action not taken.");
    }
}