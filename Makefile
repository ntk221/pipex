CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS = main.c
LIBFT = libft
NAME = pipex

all: $(NAME)

$(NAME):
	$(CC) $(SRCS) -L$(LIBFT) -o $(NAME) -lft

rm:
	rm $(NAME)

re: rm $(NAME)
