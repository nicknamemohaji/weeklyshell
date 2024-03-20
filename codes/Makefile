NAME = minishell

INPUT_FILES = 	input/input_readline.c \
				input/input_terminal.c \
				input/input_validator.c
PARSER_FILES = 
LOADER_FILES = 	loader/ldpre_param_expansion.c \
				loader/ldpre_param_quote.c \
				loader/ldpre_param_wildcard.c \
				loader/ldpre_param_wildcard2.c \
				loader/ldexec_findexec.c \
				loader/ldexec_run.c \
				loader/ldexec_heredoc.c
UTIL_FILES = 	utils/do_exit.c \
				utils/free_ft_split.c \
				utils/input_sighandler.c \
				utils/ld_chdir.c \
				utils/ld_errno_file.c \
				utils/ld_map_functions.c \
				utils/ld_map_functions2.c
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

all: $(NAME)

$(NAME): libft.a $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(INCLUDES) $(LIBRARIES)
	@echo
	@echo
	@echo $(NAME) Compiled!

%.o: %.c
	$(CC) -c $< -o $*.o $(CFLAGS) $(INCLUDES)
	
libft.a:
	@$(MAKE) -C $(LIBFT_DIR) all -j8
	@cp $(LIBFT_DIR)libft.a .
	@echo LIBFT Compiled!

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJECTS)
	@echo Cleaned!

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f libft.a
	@rm -rf $(NAME)
	@echo Fcleaned!

re: fclean all

.PHONY: all clean re fclean
