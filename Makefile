NAME = libphilo.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = philo.c \
	create_thread.c \
	error_msg.c \
	dead.c \
	ft_atoi.c \
	initialize_phils.c \
	log_functions.c \
	parsing.c \
	rotate_queue.c \
	mutex_unlock.c \

OBJ = $(SRCS:.c=.o)
EXE = philo
RM = rm -f

all: $(EXE)

$(EXE): $(NAME)
	$(CC) $(CFLAGS) $(NAME) -o $(EXE)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) $(EXE)

re: fclean all
