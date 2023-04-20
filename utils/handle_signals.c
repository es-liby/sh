/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:31:37 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/18 03:08:29 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	sigint_handler(int sig);
static void	sigint_handler_for_heredoc(int sig);

void	handle_signals(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
}

static void	sigint_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", STDIN_FILENO);
	close(STDIN_FILENO);
	g_gbl.exit_status = 1;
}

void	handle_signals_for_heredoc(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGINT, sigint_handler_for_heredoc) == SIG_ERR)
		exit(EXIT_FAILURE);
}

static void	sigint_handler_for_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", STDIN_FILENO);
	close(STDIN_FILENO);
	g_gbl.exit_status = 1;
	g_gbl.sigint = ON;
}
