CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS = main.c
NAME = pipex

all: $(NAME)

$(NAME):
	$(CC) $(SRCS) gnl.a -o $(NAME)

rm:
	rm $(NAME)

re: rm $(NAME)