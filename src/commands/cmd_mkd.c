/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file
*/

#include "ftp.h"

void cmd_mkd(client_t *client, char **splitted)
{
    if (mkdir(splitted[1], S_IRWXU | S_IRWXG | S_IRWXO) == 0) {
        send_command(client, 200, "Command okay.");
    }
}