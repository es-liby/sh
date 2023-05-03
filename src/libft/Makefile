CC := cc
CFLAGS := -Wall -Werror -Wextra
RM := rm -f
AR := ar rc
MAKEFLAGS := --no-print-directory

NAME := ../../lib/libft.a
INCLUDE := -I ../../includes/
HEADER := ../../includes/libft.h
OBJ_DIR := ../../obj/libft/

SRCS := ft_calloc.c ft_isdigit.c ft_lstadd_back.c ft_lstlast.c ft_memset.c ft_strdup.c ft_strlcpy.c \
ft_substr.c ft_atoi.c ft_isalnum.c ft_isspace.c ft_lstclear.c ft_lstnew.c ft_split.c ft_strjoin.c \
ft_strlen.c ft_bzero.c ft_isalpha.c ft_itoa.c ft_lstdelone.c ft_lstsize.c ft_strcmp.c ft_strlcat.c \
ft_strncmp.c ft_isallblank.c

OBJS = $(addprefix $(OBJ_DIR),$(SRCS:%.c=%.o))

BLUE = $(shell tput -Txterm setaf 6)
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
	@printf "\t$(SYMB) $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@\n"

clean:
	$(RM) $(OBJS) $(OBJS_BO)
fclean: clean
	$(RM) $(NAME)
re: fclean all
