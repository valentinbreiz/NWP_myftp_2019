/*
** EPITECH PROJECT, 2020
** FTPC
** File description:
** file
*/

#include "ftp.h"

void init_ftpserver(server_t *server, int port)
{
    server->sin_size = 0;
    server->fdserver = socket(AF_INET, SOCK_STREAM, 0);
    server->_server.sin_family = AF_INET;
    server->_server.sin_addr.s_addr = htonl(INADDR_ANY);
    server->_server.sin_port = htons(port);
    server->i = 1;
    setsockopt(server->fdserver, SOL_SOCKET,
    SO_REUSEPORT, &server->i, sizeof(int));
    bind(server->fdserver, (const struct sockaddr*)&server->_server,
    sizeof(server->_server));
    listen(server->fdserver, 20);
}

void init_client(client_t *client, char *localip, int port, int fdclient)
{
    client->username = NULL;
    client->localip = localip;
    client->password = NULL;
    client->serverport = port;
    client->fdclient = fdclient;
    client->fddata = -1;
    client->mode = -1;
}

void receive_new_client(int fdclient, int port, int clientcount,
char *localip)
{
    pid_t child = fork();

    if (child == 0) {
        client_t *client = malloc(sizeof(client_t));
        client->id = clientcount;
        init_client(client, localip, port, fdclient);
        send_command(client, 220, "Service ready for new user.");
        receive_command(client);
        send_command(client, 221, "Service closing control connection.");
        close(client->fdclient);
        if (client->fddata != -1)
            close(client->fddata);
        printf("FTP : Client[%d] : disconnected\n", client->id);
    }
}

int check_quit(client_t *client, char **splitted)
{
    if (strcasecmp(splitted[0], "QUIT") == 0)
        return (1);
    return (0);
}

void receive_command(client_t *client)
{
    char buffer[1024];
    char **splitted = NULL;
    memset(buffer, 0, 1024);
    while (read(client->fdclient, buffer, 1024) > 0) {
        if (strcmp(buffer, "\r\n") == 0)
            continue;
        if (buffer[strlen(buffer) - 1] == '\n' &&
        buffer[strlen(buffer) - 2] == '\r')
            buffer[strlen(buffer) - 2] = 0;
        else if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = 0;
        printf("FTP : Client[%d] : "
        "received command = '%s'\n", client->id, buffer);
        splitted = my_str_to_word_array(buffer, " ");
        if (check_quit(client, splitted))
            break;
        process_command(client, splitted);
        memset(buffer, 0, 1024);
    }
}