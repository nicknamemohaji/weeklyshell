# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/28 21:23:19 by kyungjle          #+#    #+#              #
#    Updated: 2024/04/04 18:33:38 by kyungjle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# inner-0 libft files
LIBFT_FILE_DIR = /libft
CTYPE_FILES =	ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isspace.c
STRING_FILES =	ft_strlen.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_strcmp.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_strdup.c
STDLIB_FILES = 	ft_atoi.c \
				ft_atof.c \
				ft_calloc.c
LIBFT_FILES = 	ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_ftoa.c \
				ft_itoa_base.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c

LIBFT_OBJECTS = 	$(CTYPE_FILES:.c=.o) \
					$(STRING_FILES:.c=.o) \
					$(STDLIB_FILES:.c=.o) \
					$(LIBFT_FILES:.c=.o)

# inner-1 ft_printf files
PRINTF_FILE_DIR = /ft_printf
PRINTF_FILES = 	ft_printf.c \
				fp_list.c \
				fp_parse.c \
				fp_conversion_wrapper.c \
				fp_conversion_other.c \
				fp_conversion_integer.c \
				fp_conversion_character.c

PRINTF_OBJECTS = $(PRINTF_FILES:.c=.o)

# inner-1 get_next_line files
GNL_FILE_DIR = /get_next_line
GNL_FILES = 	get_next_line.c \
				get_next_line_utils.c

GNL_OBJECTS = $(GNL_FILES:.c=.o)

# directories
SRC_DIR = srcs
HEADER_DIR = headers
OBJECT_DIR = objects
OBJECTS = 	$(LIBFT_OBJECTS) \
			$(PRINTF_OBJECTS) \
			$(GNL_OBJECTS)

# flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(HEADER_DIR)
AR = ar
ARFLAGS = rsc

all: $(NAME)

$(NAME): $(addprefix $(OBJECT_DIR)/, $(OBJECTS))
	@echo making archive
	@$(AR) $(ARFLAGS) $(NAME) $(addprefix $(OBJECT_DIR)/, $(OBJECTS))
	@echo libft compiled

$(addprefix $(OBJECT_DIR)/, $(LIBFT_OBJECTS)):
	@mkdir -p $(OBJECT_DIR)
	@$(CC) $(CFLAGS) -c $(subst $(OBJECT_DIR)/,$(SRC_DIR)$(LIBFT_FILE_DIR)/,$*).c -o $@

$(addprefix $(OBJECT_DIR)/, $(PRINTF_OBJECTS)):
	@mkdir -p $(OBJECT_DIR)
	@$(CC) $(CFLAGS) -c $(subst $(OBJECT_DIR)/,$(SRC_DIR)$(PRINTF_FILE_DIR)/,$*).c -o $@

$(addprefix $(OBJECT_DIR)/, $(GNL_OBJECTS)):
	@mkdir -p $(OBJECT_DIR)
	@$(CC) $(CFLAGS) -c $(subst $(OBJECT_DIR)/,$(SRC_DIR)$(GNL_FILE_DIR)/,$*).c -o $@

clean:
	rm -rf $(addprefix $(OBJECT_DIR)/, $(OBJECTS))

fclean: clean
	rm -rf $(NAME)

re: fclean all


.PHONY: all clean fclean re
