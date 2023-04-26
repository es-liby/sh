/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:07:43 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/26 10:31:22 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	fatal(char *msg)
{
	ft_fprintf(2, "sh: %s\n", msg);
}

void	cmd_notfound(char *cmd)
{
	ft_fprintf(2, "sh: %s: command not found\n", cmd);
}
