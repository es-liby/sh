/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:40:22 by iabkadri          #+#    #+#             */
/*   Updated: 2023/01/09 10:40:33 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>

int	ft_atoi(const char *str)
{
	long	val;
	int		sign;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	val = 0;
	while (ft_isdigit(*str))
	{
		val = val * 10 + (*str++ - '0');
		if ((val > INT_MAX && sign == 1) || (val - 1 > INT_MAX && sign == -1))
			return (-1);
	}
	return (val * sign);
}
