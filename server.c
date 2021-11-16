/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 20:03:31 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/15 19:28:01 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minitalk.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void	exit_failure(char *error)
{
	ft_putstr_fd(error, 1);
	write(1, "\n", 1);
	exit(1);
}

char	*ft_strjoinchar(char *s1, char const c)
{
	char	*ret;
	size_t	i;

	if (s1 == NULL || c == 0)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * ft_strlen(s1) + 2);
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	free(s1);
	ret[i] = c;
	i++;
	ret[i] = '\0';
	return (ret);
}

void	onebit(int sig, siginfo_t *info, void *context)
{
	int	bit;

	(void)context;
	bit = 0;
	if (g_data.str == NULL)
		g_data.str = ft_strdup("");
	if (sig == SIGUSR1)
		bit = 1;
	g_data.c |= (bit << g_data.i--);
	if (g_data.i < 0)
	{
		if (g_data.c == '\0')
		{
			ft_putendl_fd(g_data.str, 1);
			free(g_data.str);
			g_data.str = NULL;
		}
		else
			g_data.str = ft_strjoinchar(g_data.str, g_data.c);
		g_data.i = 6;
		g_data.c = 0;
	}
	usleep(500);
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
	sigemptyset(&onebit_act.sa_mask);
	if (sigaction(SIGUSR1, &onebit_act, NULL) != 0)
		exit_failure("signal error\n");
	if (sigaction(SIGUSR2, &onebit_act, NULL) != 0)
		exit_failure("signal error\n");
	pid = getpid();
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	loop();
}
