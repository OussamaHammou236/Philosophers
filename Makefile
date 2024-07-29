NAME= philosopher
CC=cc
#CFLAGS= -Wall -Wextra -Werror
CFLAGS= -fsanitize=thread #-TSAN_OPTIONS=second_deadlock_stack=1 
OBJ= ft_atoi.c ft_strlen.c philosopher.c time.c initialization.c routine.c 
OBJ_O=${OBJ:.c=.o}

all: $(NAME)

$(NAME): $(OBJ_O)
	$(CC) $(CFLAGS) $(OBJ_O) -o $(NAME)

clean:
	rm -rf $(OBJ_O)

fclean: clean
	rm -rf $(NAME)

push: fclean
	@git add .
	@git commit -m "beta_v"
	@git push

.SECONDARY: $(OBJ_O)
	
