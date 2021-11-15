/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 20:03:31 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/09 18:16:15 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minitalk.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
static void	exit_failure(char *error)
{
	ft_putstr_fd(error, 1);
	write(1, "\n", 1);
	exit(1);
}

void	onebit(int sig, siginfo_t *info, void *context)
{
	int	bit;

	(void)context;
	bit = 0;
	if (sig == SIGUSR1)
		bit = 1;
	g_data.c |= (bit << g_data.i--);
	if (g_data.i < 0)
	{
		if (g_data.c == '\0')
			write(1, "\n", 1);
		else
			write(1, &g_data.c, 1);
		g_data.i = 6;
		g_data.c = 0;
	}
	usleep(100);
	kill(info->si_pid, SIGUSR1);
}

void	loop(void)
{
	while (1)
	{
		pause();
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	onebit_act;

	onebit_act.sa_sigaction = onebit;
	onebit_act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &onebit_act, NULL) != 0)
		exit_failure("signal error\n");
	if (sigaction(SIGUSR2, &onebit_act, NULL) != 0)
		exit_failure("signal error\n");
	pid = getpid();
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	loop();
}
