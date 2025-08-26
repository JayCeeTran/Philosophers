NAME = libphilo.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = philo.c \
	create_thread.c \
	atoi_arguments.c \
	error_msg.c \
	print_mutex.c \
	ft_atoi.c \
	initialize_phils.c \
	log_functions.c \
	parsing.c \
	routine.c \
	mutex_unlock.c \
	get_time.c \

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
