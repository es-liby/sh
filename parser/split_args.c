/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:42:29 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 08:30:47 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//static char		*get_arg_word(char **args);
//static size_t	getlen(char *args);
//static void		skip_white_space(char **args);

char	**split_argslist(t_list *arglist)
{
	char	**args_sp;
	size_t	size;
	size_t	indx;

	size = ft_lstsize(arglist) + 1;
	args_sp = ft_calloc(size, sizeof(char *));
	indx = 0;
	while (arglist)
	{
		args_sp[indx++] = ft_strdup((char *)arglist->lexeme);
		advance(&arglist);
	}
	args_sp[indx] = NULL;
	return (args_sp);
}

//char	**split_args(char *args)
//{
//	char	**args_sp;
//	size_t	size;
//	size_t	indx;

//	size = getlen(args);
//	args_sp = ft_calloc(size + 1, sizeof(char *));
//	indx = 0;
//	while (*args)
//	{
//		if (*args == ' ')
//		{
//			args_sp[indx] = ft_strdup(" ");
//			args++;
//		}
//		else
//			args_sp[indx] = get_arg_word(&args);
//		skip_white_space(&args);
//		indx++;
//	}
//	args_sp[indx] = NULL;
//	return (args_sp);
//}

//static char	*get_arg_word(char **args)
//{
//	char	*word;
//	size_t	len;

//	len = 0;
//	while ((*args)[len] && !ft_isblank((*args)[len]))
//		len++;
//	word = ft_substr(*args, 0, len);
//	*args += len;
//	return (word);
//}

//static size_t	getlen(char *args)
//{
//	size_t	size;

//	size = 0;
//	while (*args)
//	{
//		if (ft_isblank(*args))
//		{
//			size++;
//			args++;
//			continue ;
//		}
//		while (*args && !ft_isblank(*args))
//			args++;
//		size++;
//		if (ft_isblank(*args))
//			args++;
//	}
//	return (size);
//}

//static void	skip_white_space(char **args)
//{
//	if (ft_isblank(**args))
//		++*args;
//}
