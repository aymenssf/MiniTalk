NAME 	= minitalk.a
CC		= cc
CFLAGS 	= -Wall -Werror -Wextra
OBJ	= $(SRC:.c=.o)
OBJB	= $(SRCB:.c=.o)

all	  : server client

server: server.c
	$(CC) $(CFLAGS) -o server server.c utils.c
client: client.c
	$(CC) $(CFLAGS) -o client client.c utils.c

bonus : server_bonus client_bonus

server_bonus : server_bonus.c
	$(CC) $(CFLAGS) -o server_bonus server_bonus.c utils.c

client_bonus : client_bonus.c
	$(CC) $(CFLAGS) -o client_bonus client_bonus.c utils.c

clean	:
	rm -f server client client_bonus server_bonus $(OBJ) $(OBJB)

fclean	: clean
	rm -f $(NAME) $(bonus)

re	:
	fclean all
