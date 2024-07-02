NAME= philosopher
CC=cc
#CFLAGS= -Wall -Wextra -Werror
#CFLAGS= -fsanitize=thread 
OBJ= ft_atoi.c ft_strlen.c philosopher.c time.c
OBJ_O=${OBJ:.c=.o}

all: $(OBJ_O)
	$(CC) $(CFLAGS) $(OBJ_O) -o $(NAME)

clean:
	rm -rf $(OBJ_O)

fclean: clean
	rm -rf $(NAME)

push: fclean
	@git add .
	@git commit -m "beta_v"
	@git push