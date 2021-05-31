/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file
*/

#include "ftp.h"

void cmd_type(client_t *client, char **splitted)
{
    if (strcmp(splitted[1], "A") == 0) {
        client->type = 0;
    }
    else if (strcmp(splitted[1], "E") == 0) {
        client->type = 1;
    }
    else if (strcmp(splitted[1], "I") == 0) {
        client->type = 2;
    }
    else {
        send_command(client, 501, "Unknown type.");
        return;
    }
    send_command(client, 200, "Command okay.");
}