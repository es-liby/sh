CC := cc
CFLAGS := -Wall -Werror -Wextra
RM := rm -f
AR := ar rc
MAKEFLAGS := --no-print-directory

NAME := ../../lib/libft.a
INCLUDE := -I ../../includes/
HEADER := ../../includes/libft.h
OBJ_DIR := ../../obj/libft/

SRCS := ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_isspace.c	\
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strcmp.c	\
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c	\
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c

OBJS = $(addprefix $(OBJ_DIR),$(SRCS:%.c=%.o))

BLUE = $(shell tput -Txterm setaf 6)
PURPLE = $(shell tput -Txterm setaf 5)
RED = $(shell tput -Txterm setaf 1)
RESET = $(shell tput -Txterm sgr0)

BOLD := $(shell tput bold)
SGR0 := $(shell tput sgr0)

SYMB := $(BOLD)$(BLUE)√$(SGR0)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^

$(OBJ_DIR)%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "$(CC) $(CFLAGS) $(INCLUDE) -c $(BOLD)$(PURPLE)$<$(SGR0) -o $(BOLD)$(BLUE)$@$(SGR0)\n"

clean:
	$(RM) $(OBJS) $(OBJS_BO)
fclean: clean
	$(RM) $(NAME)
re: fclean all
