NAME = philo
SRCS = main.c ft_atoui.c
OBJS = $(SRCS:.c=.o)
HEADER = philosophers.h
FLAGS = -Werror -Wall -Wextra -g
CC = cc

ifdef CHECK
	FLAGS = -Wall -Wextra -g -fsanitize=thread
endif

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)


re : fclean all

.PHONY: all fclean clean re
