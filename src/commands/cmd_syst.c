/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file
*/

#include "ftp.h"

void cmd_syst(client_t *client, char **splitted)
{
    send_command(client, 215, "UNIX Type: L8.");
}