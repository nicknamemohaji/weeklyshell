# result file name
NAME = libftstring.a

# compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

AR = ar
ARFLAGS = -src

SRCS = ft_string_access.c ft_string_construct.c ft_string_control.c \
		ft_string_generate.c ft_string_new.c ft_string_set_member_function.c \
		ft_string_utility.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
