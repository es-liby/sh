CC := cc
CFLAGS := -Wall -Werror -Wextra -g
INCLUDE := -I/goinfre/$(USER)/.brew/opt/readline/include -I includes
LINKS := -L/goinfre/$(USER)/.brew/opt/readline/lib -lreadline
RM := rm -rf
MAKEFLAGS := --no-print-directory

NAME := minishell

OBJ_DIR := obj/
SRC_DIR := src/
LIB_DIR := lib/

DIRS = $(addprefix $(OBJ_DIR),scanner/ parser/ utils/ utils/envvar/ execute \
execute/builtins/ libft/ ft_fprintf/)

HEADERS = $(addprefix includes/,minishell.h scanner.h parser.h structs.h symbols.h libft.h \
ft_fprintf.h execute.h)
LIBS = $(addprefix $(LIB_DIR),libft.a libftfprintf.a)

LIBFT_SRCS = $(addprefix $(SRC_DIR)libft/,ft_calloc.c ft_isdigit.c ft_lstadd_back.c ft_lstlast.c \
ft_memset.c ft_strdup.c ft_strlcpy.c ft_substr.c ft_atoi.c ft_isalnum.c ft_isspace.c ft_lstclear.c \
ft_lstnew.c ft_split.c ft_strjoin.c ft_strlen.c ft_bzero.c ft_isalpha.c ft_itoa.c ft_lstdelone.c \
ft_lstsize.c ft_strcmp.c ft_strlcat.c ft_strncmp.c ft_isallblank.c)
FPRINTF_SRCS = $(addprefix $(SRC_DIR)ft_fprintf/,ft_fprintf.c handle.c sublibft.c)

SCANNER_SRCS = $(addprefix scanner/,scan.c scanner_utils.c redir_token.c \
pipe_token.c word_token.c quote.c \
sequence.c)
SCANNER_OBJS = $(patsubst scanner/%.c,obj/scanner/%.o,$(SCANNER_SRCS))

PARSER_SRCS = $(addprefix parser/,parse.c expand.c quote_sequence.c set_members.c \
perform_redir_io.c getquote_seq.c cmd_and_args.c heredoc.c pipe_fds.c plist_utils.c \
heredoc_utils.c readlines_heredoc.c print.c split_arglist.c)
PARSER_OBJS = $(patsubst parser/%.c,obj/parser/%.o,$(PARSER_SRCS))

BUILTINS = $(addprefix builtins/,cd_pwd.c echo.c env.c exit.c export_utils.c export.c \
unset.c update_cwd.c)
 
EXEC_SRS = $(addprefix execute/,exec.c streams.c ids.c execute_builtins.c \
split_plist.c split_args.c check_cmds.c $(BUILTINS))
EXEC_OBJS = $(patsubst execute/%.c,obj/execute/%.o,$(EXEC_SRS))
 
UTILS_SRCS = $(addprefix utils/,clear.c envcpy.c handle_signals.c getenvvar.c \
getenvvar_utils.c std.c key_value.c error.c)
UTILS_OBJS = $(patsubst utils/%.c,obj/utils/%.o,$(UTILS_SRCS))

DEPENDENCIES = $(LIBFT_SRCS) $(FPRINTF_SRCS) $(HEADERS)

BLUE = $(shell tput -Txterm setaf 6)
RESET = $(shell tput -Txterm sgr0)
BOLD := $(shell tput bold)
SGR0 := $(shell tput sgr0)
SYMB := $(BOLD)$(BLUE)√$(SGR0)

.PHONY: all bonus clean fclean re

SRCS = main.c $(SCANNER_SRCS) $(PARSER_SRCS) $(UTILS_SRCS) $(EXEC_SRS)
OBJS = $(addprefix $(OBJ_DIR),$(SRCS:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(SRC_DIR)libft
	@make -C $(SRC_DIR)ft_fprintf
	@$(CC) $^ $(LIBS) $(LINKS) -o $@

$(OBJ_DIR)%.o: %.c $(DEPENDENCIES)
	@mkdir -p $(OBJ_DIR) $(LIB_DIR) $(DIRS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "\t$(SYMB) $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@\n"

clean:
	@$(RM) $(OBJ_DIR) 
fclean: clean
	@$(RM) $(NAME) $(LIB_DIR)
re: fclean all
