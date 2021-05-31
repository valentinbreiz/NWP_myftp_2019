/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file
*/

#include "ftp.h"

static ftp_commands commands[] =
{
    {"USER", &cmd_user},
    {"PASS", &cmd_pass},
    {"SYST", &cmd_syst},
    {"TYPE", &cmd_type},
    {"FEAT", &cmd_feat},
    {"PASV", &cmd_pasv},
    {"LIST", &cmd_list},
    {"PWD", &cmd_pwd},
    {"CWD", &cmd_cwd},
    {"CDUP", &cmd_cdup},
    {"MKD", &cmd_mkd},
    {"DELE", &cmd_del},
    {"RMD", &cmd_rmd},
    {"STOR", &cmd_stor},
    {"NOOP", &cmd_noop},
    {"RETR", &cmd_retr},
    {"PORT", &cmd_port},
    {"HELP", &cmd_help},
    {NULL, NULL}
};

int is_connected(client_t *client)
{
    if (client->username == NULL || client->password == NULL) {
        send_command(client, 530, "Login incorrect.");
        return (0);
    }
    if (strcasecmp(client->username, "anonymous") == 0 &&
    strcasecmp(client->password, "null") == 0) {
        return (1);
    }
    else {
        send_command(client, 530, "Login incorrect.");
        return (0);
    }
}

void process_command(client_t *client, char **splitted)
{
    int counter = 0;

    while (commands[counter].cmd != NULL) {
        if (strcmp(commands[counter].cmd, splitted[0]) == 0) {
            commands[counter].cmd_fct(client, splitted);
            return;
        }
        counter++;
    }
    send_command(client, 500, "Unknown command.");
}

void send_command(client_t *client, int id, char *text)
{
    if (id == -1) {
        printf("FTP : Client[%d] : sent %s\n", client->id, text);
        dprintf(client->fdclient, "%s\r\n", text);
    }
    else {
        printf("FTP : Client[%d] : sent %d %s\n", client->id, id, text);
        dprintf(client->fdclient, "%d %s\r\n", id, text);
    }
}