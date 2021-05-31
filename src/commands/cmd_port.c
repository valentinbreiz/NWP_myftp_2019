/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file
*/

#include "ftp.h"

void cmd_port(client_t *client, char **splitted)
{
    char **ip;

    if (is_connected(client) == 0)
        return;
    ip = my_str_to_word_array(splitted[1], ",");
    if ((client->fddata = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        send_command(client, 425, "Can't open data connection.");
    client->sockdata.sin_family = AF_INET;
    client->sockdata.sin_addr.s_addr = INADDR_ANY;
    client->sockdata.sin_port = htons((atoi(ip[4]) * 256)
    + atoi(ip[5]));
    send_command(client, 227, "Entering Active Mode.");
    client->mode = 1;
}