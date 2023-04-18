/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 10:20:21 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/18 10:36:01 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
    char*           key;
    char*           value;
    int             printed;
    int             without_equal;
    int             replace;
    struct s_env   *next;
}       t_env;

typedef struct s_list
{
    char*           value;
    struct s_list   *next;
}       t_list;

char	**ft_split(char const *s, char c);
void    freestr(char **s);
void    ft_env(char  **env);
void    ft_putstr(char  *s);
int     ft_isdigit(int c);
int	    ft_isalpha(int c);
void    ft_echo(char **str);
int     ft_strcmp(char *s1, char *s2);
void	ft_cd(char *path);
void	ft_pwd(void);
char	*ft_strdup(const char *s1);
int ft_strcmp(char *s1, char *s2);
void    ft_lstaddback_env(t_env **e, t_env *new);
t_env   *ft_lstnew_env(char *str);
void    *ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
int     ft_unset(t_env **e, char *str);
int     ft_export(t_env *e, char **env, char **new_variables);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *c);
int	    more_than_equal(char *str);
void    print_env(t_env *e);
t_env	*handle_more_than_equal(char *str);
t_env	*handle_plus_equal_and_equal_at_end(char *str);
t_env	*handle_plus_equal_and_equal_not_at_the_end(char *str);
t_env	*handle_simple_assignement(char *str);
t_env	*handle_equal_at_the_end(char *str);
t_env	*handle_ls_colors_variable(char *str);
t_env	*handle_the_rest(char *str);

#endif
