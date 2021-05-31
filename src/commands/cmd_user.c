/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file
*/

#include "ftp.h"

void cmd_user(client_t *client, char **splitted)
{
    (void)splitted;
    if (client->username != NULL && strcasecmp(splitted[1], "anonymous") == 0)
    {
        send_command(client, 230, "User logged in, proceed.");
    }
    else {
        send_command(client, 331, "User name okay, need password.");
        free(client->username);
        client->username = strdup(splitted[1]);
    }
}