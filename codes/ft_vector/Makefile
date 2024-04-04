# result file name
NAME = libftvector.a

# compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

AR = ar
ARFLAGS = -src

SRCS = ft_vector_construct.c ft_vector_new.c ft_vector_set_member_function.c \
		ft_vector_access.c ft_vector_control.c \

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
