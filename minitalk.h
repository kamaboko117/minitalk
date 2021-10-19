/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:05:52 by asaboure          #+#    #+#             */
/*   Updated: 2021/10/19 17:15:21 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define BUFFSIZE 64

typedef struct	s_data
{
	unsigned char		c;
	int					i;
	int					bit_head;
	int					byte_head;
	int					all_receive;
	int					buff_overflow;
}				t_data;

t_data	g_data = {'0', 6, 1 << 6, 0, 0, 0};

#endif