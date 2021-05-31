/*
** EPITECH PROJECT, 2020
** FTPC
** File description:
** file
*/

#ifndef FTPC_FTP_H
#define FTPC_FTP_H

#include <stdint.h>
#include "my_str_to_word_array.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

typedef struct server
{
    struct sockaddr_in _server;
    struct sockaddr_in _client;
    int fdserver;
    socklen_t sin_size;
    int i;
    int clientcount;
} server_t;

typedef struct client
{
    char *localip;
    struct sockaddr_in sockdata;
    int id;
    int serverport;
    int fdclient;
    int fdserver;
    int fddata;
    int mode;
    int type;
    char *username;
    char *password;
} client_t;

typedef struct ftpcommand_s
{
    const char *cmd;
    void (*cmd_fct)(client_t *client, char **splitted);
} ftp_commands;

void receive_command(client_t *client);
void process_command(client_t *client, char **splitted);
int check_quit(client_t *client, char **splitted);

void cmd_user(client_t *client, char **splitted);
void cmd_cwd(client_t *client, char **splitted);
void cmd_pwd(client_t *client, char **splitted);
void cmd_cdup(client_t *client, char **splitted);
void cmd_pass(client_t *client, char **splitted);
void cmd_type(client_t *client, char **splitted);
void cmd_syst(client_t *client, char **splitted);
void cmd_feat(client_t *client, char **splitted);
void cmd_pasv(client_t *client, char **splitted);
void cmd_list(client_t *client, char **splitted);
void cmd_del(client_t *client, char **splitted);
void cmd_mkd(client_t *client, char **splitted);
void cmd_rmd(client_t *client, char **splitted);
void cmd_stor(client_t *client, char **splitted);
void cmd_port(client_t *client, char **splitted);
void cmd_noop(client_t *client, char **splitted);
void cmd_retr(client_t *client, char **splitted);
void cmd_help(client_t *client, char **splitted);
void cmd_list_pasv(client_t *client, char **splitted);
void cmd_stor_pasv(client_t *client, char *path);
void cmd_retr_pasv(client_t *client, char *path);
void cmd_stor_actv(client_t *client, char *path);
void cmd_retr_actv(client_t *client, char *path);
void cmd_list_actv(client_t *client, char **splitted);
int is_connected(client_t *client);

void send_command(client_t *client, int id, char *text);

void receive_new_client(int fdclient, int port, int clientcount, char *localip);

void init_ftpserver(server_t *server, int port);

#endif //FTPC_FTP_H
