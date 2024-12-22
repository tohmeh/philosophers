/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:06:08 by mtohmeh           #+#    #+#             */
/*   Updated: 2024/12/22 16:15:22 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_program(t_program *program, int argc, char **argv)
{
	program->num_philosophers = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	program->simulation_finished = 0;
	program->all_ate_enough = 0;
	if (argc == 6)
		program->must_eat_count = ft_atoi(argv[5]);
	else
		program->must_eat_count = -1;
}

void	init_philosopher(t_philosopher *philo, t_program *program, int i)
{
	philo->program = program;
	philo->left_fork = &program->forks[i];
	philo->right_fork = &program->forks[(i + 1) % program->num_philosophers];
	philo->meals_eaten = 0;
	philo->id = i + 1;
	philo->start_time = program->start_time;
	philo->last_meal_time = get_current_time_ms();
}
