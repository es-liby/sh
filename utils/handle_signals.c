/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:31:37 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/27 09:00:48 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	sigint_handler(int sig);
static void	sigint_handler_for_heredoc(int sig);

void	handle_signals(void)
{
	rl_catch_signals = 0;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("sh: signal");
	else if (signal(SIGINT, sigint_handler) == SIG_ERR)
		perror("sh: signal");
}

void	handle_signals_for_cmds(void)
{
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit_with_errmsg("sigaction", errno, 1);
	else if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit_with_errmsg("sigaction", errno, 1);
}

static void	sigint_handler(int sig)
{
	(void)sig;
	if (waitpid(-1, NULL, WNOHANG) != -1)
		return ;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", STDIN_FILENO);
	rl_redisplay();
	update_exit_status(1);
}

void	handle_signals_for_heredoc(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("sh: signal");
	else if (signal(SIGINT, sigint_handler_for_heredoc) == SIG_ERR)
		perror("sh: signal");
}

static void	sigint_handler_for_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", STDIN_FILENO);
	close(STDIN_FILENO);
	g_gbl.sigint = ON;
	update_exit_status(1);
}
