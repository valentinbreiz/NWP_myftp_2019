/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cmd_noop
*/

#include "ftp.h"

void cmd_noop(client_t *client, char **splitted)
{
    if (is_connected(client) == 0)
        return;
    send_command(client, 200, "Command okay.");
}