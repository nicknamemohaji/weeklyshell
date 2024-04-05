NAME = minishell

INPUT_FILES = 	input/input_readline.c \
				input/input_terminal.c \
				input/input_validator.c
PARSER_FILES =	parser/ast_node.c \
				parser/get_node_type.c \
				parser/get_precedence.c \
				parser/get_token_type.c \
				parser/get_token.c \
				parser/lexer_token.c \
				parser/lexer.c \
				parser/move_redirection.c \
				parser/parse_command.c \
				parser/parse_expression.c \
				parser/parse_file.c \
				parser/parse_infix.c \
				parser/parse_parenthesis.c \
				parser/parse_prefix.c \
				parser/parse.c \
				parser/parser_cmd_list.c \
				parser/parser_error.c \
				parser/parser.c
LOADER_FILES = 	loader/ldpre_param_expansion.c \
				loader/ldpre_param_expansion2.c \
				loader/ldpre_param_quote.c \
				loader/ldpre_param_wildcard.c \
				loader/ldpre_param_wildcard2.c \
				loader/ldpre_param_wrapper.c \
				loader/ldexec_findexec.c \
				loader/ldexec_run.c \
				loader/ldexec_env_exitcode.c \
				loader/ldpre_ast.c \
				loader/ldpre_ast_redir.c \
				loader/ldpre_ast_redir_heredoc.c \
				loader/ldpre_ast_exec_execall.c \
				loader/loader_wrapper.c
UTIL_FILES = 	utils/do_exit.c \
				utils/free_ft_split.c \
				utils/input_sighandler.c \
				utils/ld_chdir.c \
				utils/ld_errno_file.c \
				utils/ld_map_functions.c \
				utils/ld_map_functions2.c \
				utils/ft_qsort.c
BUILTIN_FILES = builtins/builtin_cd.c \
				builtins/builtin_echo.c \
				builtins/builtin_exit.c \
				builtins/builtin_export.c \
				builtins/builtin_unset.c \
				builtins/builtin_env.c \
				builtins/builtin_pwd.c \
				builtins/builtin_wrapper.c
FILES = main.c \
		$(INPUT_FILES) \
		$(PARSER_FILES) \
		$(PARSER_FILES) \
		$(LOADER_FILES) \
		$(BUILTIN_FILES) \
		$(UTIL_FILES)
OBJECTS = $(FILES:.c=.o)

# libraries
LIBFT_DIR = libft/
FT_STRING_DIR = ft_string/
FT_VECTOR_DIR = ft_vector/

HEADER_DIR = includes/
INCLUDES = -I $(HEADER_DIR) -I $(LIBFT_DIR)headers/ -I $(FT_STRING_DIR) -I $(FT_VECTOR_DIR)
LIBRARIES = -lft -lftvector -lftstring -lreadline -L.

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CC = cc

all: $(NAME)

$(NAME): libft.a libftvector.a libftstring.a $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(INCLUDES) $(LIBRARIES)
	@echo
	@echo
	@echo $(NAME) Compiled!

%.o: %.c
	@echo compiling $<
	@$(CC) -c $< -o $*.o $(CFLAGS) $(INCLUDES)
	
libft.a:
	@$(MAKE) -C $(LIBFT_DIR) all -j8
	@cp $(LIBFT_DIR)libft.a .
	@echo LIBFT Compiled!

libftvector.a:
	@$(MAKE) -C $(FT_VECTOR_DIR) all -j8
	@cp $(FT_VECTOR_DIR)libftvector.a .
	@echo LIBFTVECTOR Compiled!

libftstring.a:
	@$(MAKE) -C $(FT_STRING_DIR) all -j8
	@cp $(FT_STRING_DIR)libftstring.a .
	@echo LIBFTSTRING Compiled!

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(FT_STRING_DIR) clean
	@$(MAKE) -C $(FT_VECTOR_DIR) clean
	@rm -rf $(OBJECTS)
	@echo Cleaned!

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(FT_STRING_DIR) fclean
	@$(MAKE) -C $(FT_VECTOR_DIR) fclean
	@rm -f libft.a libftvector.a libftstring.a
	@rm -rf $(NAME)
	@echo Fcleaned!

re: fclean all

.PHONY: all clean re fclean
