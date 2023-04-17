/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 22:49:38 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 00:12:05 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	sigint_handler(int sig);

int	handle_signals_for_heredoc(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (EOF);
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		return (EOF);
	return (true);
}

static void	sigint_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	close(0);
	g_gbl.sigint = ON;
	g_gbl.exit_status = 1;
}
