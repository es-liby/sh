/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isallblank.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:12:15 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 18:15:11 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

bool	ft_isallblank(const char *str)
{
	while (*str && ft_isblank(*str))
		str++;
	return (*str == 0);
}

bool	ft_isblank(char c)
{
	return (c == ' ' || c == '\t');
}
