NAME = minishell

INPUT_FILES = 	input/input_readline.c \
				input/input_terminal.c \
				input/input_sighandler.c \
				input/input_validator.c
PARSER_FILES = 
LOADER_FILES = 
FILES = main.c \
		$(INPUT_FILES) \
		$(PARSER_FILES) \
		$(LOADER_FILES)
OBJECTS = $(FILES:.c=.o)
LIBFT_DIR = libft/

HEADER_DIR = includes/
INCLUDES = -I $(HEADER_DIR) -I $(LIBFT_DIR)
LIBRARIES = -lft -lreadline -L.

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address $(INCLUDES) $(LIBRARIES)
CC = gcc

$(NAME): libft.a $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(NAME)
	echo $(NAME) Compiled!

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $*.o $(INCLUDES) $(LIBRARIES)
	
libft.a:
	@$(MAKE) -C $(LIBFT_DIR) all -j8
	@cp $(LIBFT_DIR)libft.a .
	echo LIBFT Compiled!

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJECTS)
	echo Cleaned!

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f libft.a
	@rm -rf $(NAME)
	echo Fcleaned!

re: fclean all

.PHONY: clean
