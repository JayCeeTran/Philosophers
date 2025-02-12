NAME = libphilo.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = philo.c \
	error_msg.c \
	destroy_mutex_left_right.c \
	ft_atoi.c \
	initialize_phils.c \
	log_functions.c \
	parsing.c \


OBJ = $(SRCS:.c=.o)
EXE = philo
RM = rm -r

all: $(EXE)

$(EXE): $(NAME)
	$(CC) $(CFLAGS) $(NAME) -o $(EXE)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	make clean

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(NAME) $(EXE)

re: fclean all
