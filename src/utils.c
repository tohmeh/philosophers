/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:08:15 by mtohmeh           #+#    #+#             */
/*   Updated: 2024/12/22 17:06:41 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	sign;

	sign = 1;
	n = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	return (n * sign);
}

int	count_2d_char_array_rows(char **arr)
{
	int	count;

	count = 0;
	while (arr[count] != NULL)
		count++;
	return (count);
}

int	only_numbers_check(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	argument_validation(char **argv)
{
	int	len;
	int	i;

	i = 1;
	len = count_2d_char_array_rows(argv);
	if (len != 5 && len != 6)
		return (0);
	while (i < len - 1)
	{
		if (!only_numbers_check(argv[i]) || ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	if (len == 6)
	{
		if (!only_numbers_check(argv[i]) || ft_atoi(argv[i]) <= 0)
			return (0);
	}
	return (1);
}

void	print_state(t_philosopher *philo, char *state)
{
	pthread_mutex_lock(&philo->program->print_mutex);
	if (!philo->program->simulation_finished)
		printf("%lld %d %s\n", get_elapsed_time(philo->start_time),
			philo->id, state);
	pthread_mutex_unlock(&philo->program->print_mutex);
}
