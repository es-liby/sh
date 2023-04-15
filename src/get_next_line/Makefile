CC := cc
CFLAGS := -Wall -Werror -Wextra
AR := ar rc
RM := rm -f
MAKEFLAGS := --no-print-directory

NAME := ../../lib/libgnl.a
INCLUDE := -I ../../includes/
HEADER := ../../includes/get_next_line.h
OBJ_DIR := ../../obj/get_next_line/

SRCS := get_next_line.c	\
		get_next_line_utils.c
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
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
