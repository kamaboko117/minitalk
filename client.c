/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:41:10 by asaboure          #+#    #+#             */
/*   Updated: 2021/10/19 17:33:37 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void	exit_failure(char *error)
{
	ft_putstr_fd(error, 1);
	write(1, "\n", 1);
	exit(1);
}

void	sendchar(unsigned char c, int pid)
{
	int	i;
	
	i = 1 << 6;
	while (i)
	{
		if (i & c)
		{
			//ft_putnbr_fd(1, 1);
			if (kill(pid, SIGUSR1) == -1)
				exit_failure("wrong PID\n");
		}
		else
		{
			//ft_putnbr_fd(0, 1);
			if (kill(pid, SIGUSR2) == -1)
				exit_failure("wrong PID\n");
		}
		i >>= 1;
		usleep(1000);
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc != 3)
	{
		ft_putstr_fd("wrong number of arguments\n", 1);
		return (-1);
	}
	pid = ft_atoi(argv[1]);
	i = 0;
	while(argv[2][i])
	{
		sendchar(argv[2][i], pid);
		i++;
	}
	sendchar(0, pid);
//	sigaddset(set, SIGUSR1);
//	sigaction(SIGUSR1, q);
}