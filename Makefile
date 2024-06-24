NAME= philosopher
CC=cc
#CFLAGS= -Wall -Wextra -Werror
OBJ= ft_atoi.c ft_strlen.c philosopher.c
OBJ_O=${OBJ:.c=.o}

all: $(OBJ_O)
	$(CC) $(CFLAGS) $(OBJ_O) -o $(NAME)

clean:
	rm -rf $(OBJ_O)

flcean: clean
	rm -rf $(NAME)
