/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:43:53 by mtohmeh           #+#    #+#             */
/*   Updated: 2024/12/22 15:58:14 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	create_fork_mutexes(t_program *program)
{
	int	i;

	i = 0;
	program->forks = malloc(sizeof(pthread_mutex_t)
			* program->num_philosophers);
	if (!program->forks)
		return (0);
	while (i < program->num_philosophers)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&program->forks[i]);
			free(program->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

int	create_secondary_mutexes(t_program *program)
{
	if (pthread_mutex_init(&program->print_mutex, NULL) != 0
		|| pthread_mutex_init(&program->death_mutex, NULL) != 0
		|| pthread_mutex_init(&program->all_ate_enough_mutex, NULL) != 0
		|| pthread_mutex_init(&program->meals_mutex, NULL) != 0)
	{
		cleanup_mutexes(program);
		return (0);
	}
	return (1);
}

int	create_mutexes(t_program *program)
{
	if (!create_fork_mutexes(program))
		return (0);
	if (!create_secondary_mutexes(program))
		return (0);
	return (1);
}
