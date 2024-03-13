NAME = minishell

INPUT_FILES = 	input/input_readline.c \
				input/input_terminal.c \
				input/input_sighandler.c \
				input/input_validator.c
PARSER_FILES = 
LOADER_FILES = 	loader/ldexec_findexec.c
UTIL_FILES = 	utils/do_exit.c \
				utils/free_ft_split.c \
				utils/ld_chdir.c
FILES = main.c \
		$(INPUT_FILES) \
		$(PARSER_FILES) \
		$(LOADER_FILES) \
		$(UTIL_FILES)
OBJECTS = $(FILES:.c=.o)
LIBFT_DIR = libft/

HEADER_DIR = includes/
INCLUDES = -I $(HEADER_DIR) -I $(LIBFT_DIR)headers/
LIBRARIES = -lft -lreadline -L.

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CC = cc

$(NAME): libft.a $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(INCLUDES) $(LIBRARIES)
	echo $(NAME) Compiled!

%.o: %.c
	$(CC) -c $< -o $*.o $(CFLAGS) $(INCLUDES)
	
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