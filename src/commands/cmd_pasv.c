/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file
*/

#include "ftp.h"
#include "include.h"

void cmd_pasv(client_t *client, char **splitted)
{
    int port;
    if (is_connected(client) == 0)
        return;
    if ((client->fddata = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        send_command(client, 425, "Can't open data connection.");
    client->sockdata.sin_family = AF_INET;
    client->sockdata.sin_addr.s_addr = htonl(INADDR_ANY);
    client->sockdata.sin_port = htons(port = 1333);
    while (bind(client->fddata, (const struct sockaddr*)&client->sockdata,
    sizeof(client->sockdata)) < 0)
        client->sockdata.sin_port = htons((port = rand() % (64611) + 1024));
    if (listen(client->fddata, 20) != 0)
        send_command(client, 425, "Can't open data connection.");
    char buffer[1024];
    memset(buffer, 0, 1024);
    char **parsed = my_str_to_word_array(client->localip, ".");
    sprintf(buffer,"Entering Passive Mode (%s,%s,%s,%s,%d,%d)",
    parsed[0], parsed[1], parsed[2], parsed[3], port / 256, port % 256);
    send_command(client, 227, buffer);
    client->mode = 0;
}