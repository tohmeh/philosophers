/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:19:57 by mtohmeh           #+#    #+#             */
/*   Updated: 2024/12/23 19:06:09 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	print_state(philo, "has taken left fork");
	print_state(philo, "has taken right fork");
}

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->program->meals_mutex);
	if (simulation_should_stop(philo))
	{
		pthread_mutex_unlock(&philo->program->meals_mutex);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	philo->last_meal_time = get_current_time_ms();
	print_state(philo, GREEN "is eating" RESET);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->program->meals_mutex);
	usleep(philo->program->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

int	simulation_should_stop(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->program->death_mutex);
	if (philo->program->simulation_finished || philo->program->all_ate_enough)
	{
		pthread_mutex_unlock(&philo->program->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->program->death_mutex);
	return (0);
}

void	sleeping(t_philosopher *philo)
{
	print_state(philo, CYAN "is sleeping" RESET);
	usleep(philo->program->time_to_sleep * 1000);
}

void	thinking(t_philosopher *philo)
{
	print_state(philo, "is thinking");
}
