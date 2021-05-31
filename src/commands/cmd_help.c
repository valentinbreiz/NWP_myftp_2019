/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file
*/

#include "ftp.h"

void cmd_help(client_t *client, char **splitted)
{
    if (is_connected(client) == 0)
        return;
    send_command(client, 214, "The following commands are recognized.");
    send_command(client, -1, " CDUP CWD DEL FEAT HELP LIST MKD NOOP TYPE\n");
    send_command(client, -1, " PASS PASV PORT PWD RETR RMD STOR SYST USER\n");
    send_command(client, 214, "Help done.");
}