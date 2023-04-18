# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/09 12:07:25 by yel-hajj          #+#    #+#              #
#    Updated: 2023/04/17 15:11:47 by yel-hajj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wetra -Werror
FRM = rm -rf

NAME = minishell
HEADER = exec.h

SRCMAN = exec.c \
		split.c \
		env.c \
		echo.c \
		pwd_cd_unset_exit.c \
		export.c \
		env_fns1.c \
		env_fns2.c \
		libft_fns.c \

all : $(NAME)

$(NAME) : $(SRCMAN) $(HEADER)
	$(CC) $(FLAGS) $(SRCMAN) -o $(NAME)

clean : 
	$(FRM) $(NAME)

re : clean all