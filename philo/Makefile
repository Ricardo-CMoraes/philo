NAME = philo

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

SRC = clean.c \
	init.c \
	monitor.c \
	philo.c \
	routine.c \
	utils.c \
	validate.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re