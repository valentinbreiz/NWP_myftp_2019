/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file
*/

#include "ftp.h"

void cmd_pass(client_t *client, char **splitted)
{
    if (strcasecmp(client->username, "anonymous")) {
        send_command(client, 530, "Login incorrect.");
    }
    else if (client->username == NULL) {
        send_command(client, 332, "Need account for login.");
    }
    else {
        send_command(client, 230, "User logged in, proceed.");
        client->password = strdup("null");
    }
}