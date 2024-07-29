NAME= philo
CC=cc
CFLAGS= -Wall -Wextra -Werror -fsanitize=thread
# CFLAGS= -fsanitize=thread #-TSAN_OPTIONS=second_deadlock_stack=1 
OBJ= ft_atoi.c ft_strlen.c philosopher.c time.c initialization.c routine.c free_memory.c
OBJ_O=${OBJ:.c=.o}

all: $(NAME)

$(NAME): $(OBJ_O)
	$(CC) $(CFLAGS) $(OBJ_O) -o $(NAME)

clean:
	rm -rf $(OBJ_O)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.SECONDARY: $(OBJ_O)
	
