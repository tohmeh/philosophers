/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:06:31 by mtohmeh           #+#    #+#             */
/*   Updated: 2024/12/22 17:06:47 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	create_philosophers(t_program *program)
{
	int	i;

	program->philosophers = malloc(sizeof(pthread_t)
			* program->num_philosophers);
	if (!program->philosophers)
		return (0);
	i = 0;
	while (i < program->num_philosophers)
	{
		init_philosopher(&program->philo_arr[i], program, i);
		if (pthread_create(&program->philosophers[i], NULL,
				philosopher_routine, &program->philo_arr[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(program->philosophers[i], NULL);
			return (0);
		}
		i++;
	}
	return (1);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		if (simulation_should_stop(philo))
		{
			break ;
		}
		take_forks(philo);
		eat(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
