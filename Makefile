CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS = main.c get_path.c utils.c get_command.c
OBJS = $(SRCS:%.c=%.o)
LIBFT = libft
NAME = pipex

.PHONY: clean re all fclean

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -o $(NAME) -lft

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $? -c 
	@touch $(OBJS)

fclean: clean 
	@rm -f $(NAME)

re: fclean all

clean: 
	@rm -f $(OBJS)

