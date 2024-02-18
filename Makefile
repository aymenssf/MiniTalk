NAME 	= minitalk.a
CC	= cc
CFLAGS 	= -Wall -Werror -Wextra
SRC	= server.c client.c
OBJ	= $(SRC:.c=.o)
 
all	: $(NAME)

$(NAME)	: $(OBJ)
	$(CC) $(CFLAGS)  $(OBJ) -o $(NAME)

clean	:
	rm -f $(OBJ)

fclean	:
	rm -f $(OBJ)

re	:
	fclean all