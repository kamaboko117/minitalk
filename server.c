/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 20:03:31 by asaboure          #+#    #+#             */
/*   Updated: 2021/10/19 17:32:42 by asaboure         ###   ########.fr       */
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

/*translating every SIGUSR1 received into a 1 bit on our global byte. the buff
overflow flag is used to print the string whenever it becomes too big*/  

void	onebit(int sig, siginfo_t *info, void *context)
{
	int	bit;
	
	(void)context;
	(void)info;
	bit = 0;
	if (sig == SIGUSR1)
		bit = 1;
	g_data.c |= (bit << g_data.i--);
	if (g_data.i < 0)
    {
    	if (g_data.c == '\0')
		{
			write(1, "\n", 1);
			write(1, &g_data.c, 1);
		}
    	else
			write(1, &g_data.c, 1);
    	g_data.i = 6;
    	g_data.c = 0;
    }
}

/*same thing but with zeroes. SIGUSR1 is sent back to client once all data has
been received*/

/*void		zerobit(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	(void)info;
	if (!g_data.bit_head)
	{
		g_data.bit_head = 1 << 6;
		++(g_data.byte_head);
	}
	g_data.bit_head >>= 1;
	if (g_data.byte_head == BUFFSIZE - 2 && !g_data.bit_head)
		g_data.buff_overflow = 1;
	else if (!g_data.c && !g_data.bit_head)
	{
		g_data.all_receive = 1;
	//	kill(info->si_pid, SIGUSR1);
	}
}
*/
void	loop(void)
{
	while (1)
	{
		if (usleep(50000) == 0)
		{
			g_data.c = 0;
			g_data.i = 6;
		}
		pause();
	}
}

int	main(void)
{
	int	pid;
	struct sigaction onebit_act;

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