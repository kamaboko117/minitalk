/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:05:52 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/15 19:02:44 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

typedef struct s_data
{
	char	c;
	int		i;
}				t_data;

t_data	g_data = {0, 6};

#endif