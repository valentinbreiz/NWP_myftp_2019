##
## EPITECH PROJECT, 2020
## ASM_minilibc_2019
## File description:
## Makefile
##

.PHONY			: 	all clean fclean re

NAME			=	myftp

SRC 			=	src/main.c \
					src/utils.c \
					src/ftp.c \
					src/commands.c \
					src/commands/cmd_cdup.c \
					src/commands/cmd_cwd.c \
					src/commands/cmd_feat.c \
					src/commands/cmd_list.c \
					src/commands/cmd_pass.c \
					src/commands/cmd_pasv.c \
					src/commands/cmd_pwd.c \
					src/commands/cmd_syst.c \
					src/commands/cmd_type.c \
					src/commands/cmd_user.c \
					src/commands/cmd_del.c \
					src/commands/cmd_mkd.c \
					src/commands/cmd_rmd.c \
					src/commands/cmd_stor.c \
					src/commands/cmd_port.c \
					src/commands/cmd_noop.c \
					src/commands/cmd_retr.c \
					src/commands/cmd_help.c \
					src/my_str_to_word_array.c

OBJ				= 	$(SRC:.c=.o)

CC				= 	gcc

CFLAGS 			+=  -Wextra -I./include -g -Werror

all				:	$(NAME)

$(NAME)			:	$(OBJ)
					$(CC) -o $(NAME) $(OBJ)

clean			:
					rm -f $(OBJ)

fclean			:	clean
					rm -f $(NAME)

re				:	fclean all