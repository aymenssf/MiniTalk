NAME 	= minitalk.a
CC	= cc
CFLAGS 	= -Wall -Werror -Wextra -ggdb3 fsanitize=address
SRC	= server.c client.c
OBJ	= $(SRC:.c=.o)
 
all	: server client

server: server.c
	$(CC) $(CFLAGS) -o server server.c
client: client.c
	$(CC) $(CFLAGS) -o client client.c

clean	:
	rm -f server client $(OBJ)

fclean	: clean
	rm -f $(NAME)

re	:
	fclean all