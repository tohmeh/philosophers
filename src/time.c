/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:02:23 by mtohmeh           #+#    #+#             */
/*   Updated: 2024/12/22 17:06:44 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	get_current_time_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((long long)(current_time.tv_sec)
		*1000 + (current_time.tv_usec) / 1000);
}

void	init_time(t_program *program)
{
	program->start_time = get_current_time_ms();
}

long long	get_elapsed_time(long long start_time)
{
	return (get_current_time_ms() - start_time);
}
