/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:07:19 by mtohmeh           #+#    #+#             */
/*   Updated: 2024/12/24 20:08:35 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_death(t_philosopher *philo)
{
	long long	current_time;
	long long	last_meal;

	pthread_mutex_lock(&philo->program->meals_mutex);
	current_time = get_current_time_ms();
	last_meal = philo->last_meal_time;
	if (current_time - last_meal > philo->program->time_to_die)
	{
		pthread_mutex_lock(&philo->program->death_mutex);
		if (!philo->program->simulation_finished)
		{
			pthread_mutex_lock(&philo->program->print_mutex);
			printf("%lld %d %s\n",
				get_elapsed_time(philo->start_time), philo->id, "died");
			pthread_mutex_unlock(&philo->program->print_mutex);
			philo->program->simulation_finished = 1;
			pthread_mutex_unlock(&philo->program->death_mutex);
			pthread_mutex_unlock(&philo->program->meals_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->program->death_mutex);
	}
	pthread_mutex_unlock(&philo->program->meals_mutex);
	return (0);
}

int	check_philosophers_meals(t_program *program, t_philosopher *philosophers)
{
	int	i;
	int	all_ate_required;

	i = 0;
	all_ate_required = 1;
	if (program->must_eat_count == -1)
		return (0);
	while (i < program->num_philosophers)
	{
		pthread_mutex_lock(&program->meals_mutex);
		if (philosophers[i].meals_eaten < program->must_eat_count)
			all_ate_required = 0;
		pthread_mutex_unlock(&program->meals_mutex);
		i++;
	}
	if (all_ate_required)
	{
		pthread_mutex_lock(&program->death_mutex);
		program->all_ate_enough = 1;
		pthread_mutex_unlock(&program->death_mutex);
		return (1);
	}
	return (0);
}

void	monitor_philosophers(t_program *program, t_philosopher *philosophers)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < program->num_philosophers)
		{
			if (check_death(&philosophers[i]))
				return ;
			i++;
		}
		if (check_philosophers_meals(program, philosophers))
			return ;
		usleep(100);
	}
}
