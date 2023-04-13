CC := cc
# CFLAGS := -fsanitize=address -Wall -Werror -Wextra -g
CFLAGS := -Wall -Werror -Wextra -g
INCLUDE := -I includes/
LINKS := -lreadline
RM := rm -rf
MAKEFLAGS := --no-print-directory

NAME := minishell

OBJ_DIR := obj/
SRC_DIR := src/
LIB_DIR := lib/

DIRS = $(addprefix $(OBJ_DIR),scanner/ parser/ utils/ utils/envvar/ libft/ ft_fprintf/ get_next_line/)

HEADERS = $(addprefix includes/,minishell.h scanner.h parser.h structs.h symbols.h libft.h \
ft_fprintf.h get_next_line.h)
LIBS = $(addprefix $(LIB_DIR),libft.a libftfprintf.a libgnl.a)


LIBFT_SRCS = $(wildcard $(SRC_DIR)libft/*.c)
FPRINTF_SRCS = $(wildcard $(SRC_DIR)ft_fprintf/*.c)
GNL_SRCS = $(wildcard $(SRC_DIR)get_next_line/*.c)

MAIN := main.c
MAIN_OBJ := $(addprefix $(OBJ_DIR),$(MAIN:%.c=%.o))

#	the source files of the scannner
SCANNER_SRCS = $(addprefix scanner/,scanner.c scanner_utils.c redir_token.c \
pipe_token.c word_token.c envvar_token.c quote_token.c quote.c \
sequence.c)
SCANNER_OBJS = $(patsubst scanner/%.c,obj/scanner/%.o,$(SCANNER_SRCS))

#	the source files of the parser
PARSER_SRCS = $(addprefix parser/,parser.c expand.c quote_sequence.c redirections.c \
redir.c cmd_and_args.c heredoc.c)
PARSER_OBJS = $(patsubst parser/%.c,obj/parser/%.o,$(PARSER_SRCS))
 
# #	the source files of envvar
# ENVVAR_SRCS = $(addprefix utils/envvar/,envvar.c envcpy.c getval.c getvar.c qmark.c)
# ENVVAR_OBJS = $(patsubst utils/envvar/%.c,obj/utils/envvar/%.o,$(ENVVAR_SRCS))

#	the source files of utils
UTILS_SRCS = $(addprefix utils/,utils.c envcpy.c getenvvar.c std.c)
UTILS_OBJS = $(patsubst utils/%.c,obj/utils/%.o,$(UTILS_SRCS))

#DEPENDENCIES = $(SCANNER_SRCS) $(PARSER_SRCS) $(UTILS_SRCS) $(LIBFT_SRCS) \
$(FPRINTF_SRCS) $(GNL_SRCS) $(HEADERS)
DEPENDENCIES = $(SCANNER_SRCS) $(LIBFT_SRCS) $(FPRINTF_SRCS) $(GNL_SRCS) \
$(HEADERS)

BLUE = $(shell tput -Txterm setaf 6)
PURPLE = $(shell tput -Txterm setaf 5)
RED = $(shell tput -Txterm setaf 1)
RESET = $(shell tput -Txterm sgr0)

BOLD := $(shell tput bold)
SGR0 := $(shell tput sgr0)

SYMB := $(BOLD)$(BLUE)√$(SGR0)

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(MAIN_OBJ) $(UTILS_OBJS) $(SCANNER_OBJS) $(PARSER_OBJS)
	@make -C $(SRC_DIR)libft
	@make -C $(SRC_DIR)ft_fprintf
	@make -C $(SRC_DIR)get_next_line
	@$(CC) $^ $(LIBS) $(LINKS) -o $@
	@printf "\n"
#	@printf "\n\t$(RED)--------------------------------------------$(RESET)\n"
#	@printf "\t$(BOLD)---------> Build $(RED)minishell$(RESET)$(SGR0)\n"
#	@printf "\t$(RED)--------------------------------------------$(RESET)\n"

$(OBJ_DIR)%.o: %.c $(DEPENDENCIES)
	@mkdir -p $(OBJ_DIR) $(LIB_DIR) $(DIRS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "%-150s\r" "$(CC) $(CFLAGS) $(INCLUDE) -c $(BOLD)$(PURPLE)$<$(SGR0) -o $(BOLD)$(BLUE)$@$(SGR0)"

$(OBJ_DIR)scanner/%.o: scanner/%.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "%-150s\r" "$(CC) $(CFLAGS) $(INCLUDE) -c $(BOLD)$(PURPLE)$<$(SGR0) -o $(BOLD)$(BLUE)$@$(SGR0)"

$(OBJ_DIR)utils/%.o: utils/%.c $(DEPENDENCIES) $(MAIN)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "%-150s\r" "$(CC) $(CFLAGS) $(INCLUDE) -c $(BOLD)$(PURPLE)$<$(SGR0) -o $(BOLD)$(BLUE)$@$(SGR0)"

$(OBJ_DIR)parser/%.o: parser/%.c $(DEPENDENCIES) $(MAIN)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "%-150s\r" "$(CC) $(CFLAGS) $(INCLUDE) -c $(BOLD)$(PURPLE)$<$(SGR0) -o $(BOLD)$(BLUE)$@$(SGR0)"

# $(OBJ_DIR)utils/envvar/%.o: utils/envvar/%.c $(DEPENDENCIES) $(MAIN)
# 	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
# 	@printf "$(BOLD)$(BLUE)\t\tCompiling$(SGR0)\r"

clean:
	@$(RM) $(OBJ_DIR) 
fclean: clean
	@$(RM) $(NAME) $(LIB_DIR)
re: fclean all
