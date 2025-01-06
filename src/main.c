/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:05:47 by mtohmeh           #+#    #+#             */
/*   Updated: 2024/12/25 13:04:03 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	parse_input(char **argv, int argc, t_program *program)
{
	if (!argument_validation(argv))
	{
		perror("invalid input");
		exit (1);
	}
	init_program(program, argc, argv);
	if (program->num_philosophers == 1)
	{
		printf("0 1 died");
		exit(0);
	}
}

void	setup_table(t_program *program)
{
	if (!create_mutexes(program))
	{
		printf("Failed to initialize mutexes\n");
		exit (1);
	}
	init_time(program);
	program->philo_arr = malloc(sizeof(t_philosopher)
			* program->num_philosophers);
	if (!program->philo_arr)
	{
		cleanup_mutexes(program);
		exit (1);
	}
	if (!create_philosophers(program))
	{
		cleanup_mutexes(program);
		free(program->philo_arr);
		exit (1);
	}
}

void	unset_table(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philosophers)
	{
		pthread_join(program->philosophers[i], NULL);
		i++;
	}
	cleanup_program(program);
}

int	main(int argc, char **argv)
{
	t_program	program;

	parse_input(argv, argc, &program);
	setup_table(&program);
	monitor_philosophers(&program, program.philo_arr);
	unset_table(&program);
	return (0);
}
