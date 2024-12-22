/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:07:49 by mtohmeh           #+#    #+#             */
/*   Updated: 2024/12/22 17:06:17 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* cleanup.c */
#include "../include/philosophers.h"

void	cleanup_mutexes(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philosophers)
	{
		pthread_mutex_destroy(&program->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&program->print_mutex);
	pthread_mutex_destroy(&program->death_mutex);
	pthread_mutex_destroy(&program->all_ate_enough_mutex);
	pthread_mutex_destroy(&program->meals_mutex);
	free(program->forks);
}

void	cleanup_program(t_program *program)
{
	cleanup_mutexes(program);
	free(program->philosophers);
	free(program->philo_arr);
}
