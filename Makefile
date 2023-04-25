CC := cc
READLINE_PATH=$(shell brew --prefix readline)
CFLAGS := -Wall -Werror -Wextra -g
INCLUDE := -I $(READLINE_PATH)/include -I includes -I include
LINKS := -L $(READLINE_PATH)/lib -lreadline
RM := rm -rf
MAKEFLAGS := --no-print-directory

NAME := minishell

OBJ_DIR := obj/
SRC_DIR := src/
LIB_DIR := lib/

DIRS = $(addprefix $(OBJ_DIR),scanner/ parser/ utils/ utils/envvar/ execute\
execute/builtins/ libft/ ft_fprintf/ get_next_line/)

HEADERS = $(addprefix includes/,minishell.h scanner.h parser.h structs.h symbols.h libft.h \
ft_fprintf.h get_next_line.h execute.h)
LIBS = $(addprefix $(LIB_DIR),libft.a libftfprintf.a libgnl.a)

LIBFT_SRCS = $(addprefix $(SRC_DIR)libft/,ft_calloc.c ft_isdigit.c ft_lstadd_back.c ft_lstlast.c ft_memset.c ft_strdup.c ft_strlcpy.c \
ft_substr.c ft_atoi.c ft_isalnum.c ft_isspace.c ft_lstclear.c ft_lstnew.c ft_split.c ft_strjoin.c \
ft_strlen.c ft_bzero.c ft_isalpha.c ft_itoa.c ft_lstdelone.c ft_lstsize.c ft_strcmp.c ft_strlcat.c \
ft_strncmp.c)
FPRINTF_SRCS = $(addprefix $(SRC_DIR)ft_fprintf/,ft_fprintf.c handle.c sublibft.c)
GNL_SRCS = $(addprefix $(SRC_DIR)get_next_line/,get_next_line.c get_next_line_utils.c)

MAIN := main.c
MAIN_OBJ := $(addprefix $(OBJ_DIR),$(MAIN:%.c=%.o))

#	the source files of the scannner
SCANNER_SRCS = $(addprefix scanner/,scanner.c scanner_utils.c redir_token.c \
pipe_token.c word_token.c envvar_token.c quote_token.c quote.c \
sequence.c)
SCANNER_OBJS = $(patsubst scanner/%.c,obj/scanner/%.o,$(SCANNER_SRCS))

#	the source files of the parser
PARSER_SRCS = $(addprefix parser/,parser.c expand.c quote_sequence.c set_members.c \
perform_redir_io.c getquote_seq.c cmd_and_args.c heredoc.c io_streams.c pipe_fds.c plist_utils.c \
heredoc_utils.c readlines_heredoc.c print.c split_args.c)
PARSER_OBJS = $(patsubst parser/%.c,obj/parser/%.o,$(PARSER_SRCS))

BUILTINS = $(addprefix builtins/,cd_pwd.c echo.c env.c exit.c export_utils.c export.c \
unset.c)
 
#	the source files of execute
EXEC_SRS = $(addprefix execute/,exec.c exec_builtin.c streams.c ids.c \
search_path.c getpath.c split_plist.c $(BUILTINS))
EXEC_OBJS = $(patsubst execute/%.c,obj/execute/%.o,$(EXEC_SRS))
 
#	the source files of utils
UTILS_SRCS = $(addprefix utils/,clear.c envcpy.c handle_signals.c getenvvar.c \
getenvvar_utils.c std.c debug.c key_value.c error.c)
UTILS_OBJS = $(patsubst utils/%.c,obj/utils/%.o,$(UTILS_SRCS))

DEPENDENCIES = $(SCANNER_SRCS) $(LIBFT_SRCS) $(FPRINTF_SRCS) $(GNL_SRCS) \
$(HEADERS)

BLUE = $(shell tput -Txterm setaf 6)
RESET = $(shell tput -Txterm sgr0)

BOLD := $(shell tput bold)
SGR0 := $(shell tput sgr0)

SYMB := $(BOLD)$(BLUE)√$(SGR0)

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(MAIN_OBJ) $(UTILS_OBJS) $(SCANNER_OBJS) $(PARSER_OBJS) $(EXEC_OBJS)
	@make -C $(SRC_DIR)libft
	@make -C $(SRC_DIR)ft_fprintf
	@make -C $(SRC_DIR)get_next_line
	@$(CC) $^ $(LIBS) $(LINKS) -o $@

$(OBJ_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(OBJ_DIR) $(LIB_DIR) $(DIRS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "\t$(SYMB) $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@\n"

$(OBJ_DIR)scanner/%.o: scanner/%.c $(HEADERS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "\t$(SYMB) $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@\n"

$(OBJ_DIR)utils/%.o: utils/%.c $(HEADERS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "\t$(SYMB) $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@\n"

$(OBJ_DIR)parser/%.o: parser/%.c $(HEADERS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "\t$(SYMB) $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@\n"

$(OBJ_DIR)execute/%.o: execute/%.c $(HEADERS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "\t$(SYMB) $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@\n"

clean:
	@$(RM) $(OBJ_DIR) 
fclean: clean
	@$(RM) $(NAME) $(LIB_DIR)
re: fclean all
