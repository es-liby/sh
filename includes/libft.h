/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:34:01 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 08:28:02 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <symbols.h>
# include <stdbool.h>

typedef struct s_list
{
	t_tokentype		type;
	void			*lexeme;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isspace(int c);
bool		ft_isallblank(const char *str);
bool		ft_isblank(char c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
long		ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char const *s2);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);

t_list		*ft_lstnew(void *lexeme, t_tokentype type);
int			ft_lstsize(t_list *stk);
t_list		*ft_lstlast(t_list *stk);
void		ft_lstadd_back(t_list **stk, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **stk, void (*del)(void *));

#endif
