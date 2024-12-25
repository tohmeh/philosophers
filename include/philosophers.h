/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:02:48 by mtohmeh           #+#    #+#             */
/*   Updated: 2024/12/24 19:23:02 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* philosophers.h */
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define CYAN "\033[36m"

typedef struct s_philosopher
{
	int					id;
	long				last_meal_time;
	int					meals_eaten;
	long long			start_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_program	*program;
}	t_philosopher;

typedef struct s_program
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				simulation_finished;
	int				all_ate_enough;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	all_ate_enough_mutex;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	global_mutex;
	pthread_t		*philosophers;
	t_philosopher	*philo_arr;
	long long		start_time;
}	t_program;

// Time functions
long long	get_current_time_ms(void);
void		init_time(t_program *program);
long long	get_elapsed_time(long long start_time);

// Initialization functions
void		init_program(t_program *program, int argc, char **argv);
void		init_philosopher(t_philosopher *philo, t_program *program, int i);

//mutexes functions 
int			create_mutexes(t_program *program);

// Philosopher functions
int			create_philosophers(t_program *program);
void		*philosopher_routine(void *arg);
void		print_state(t_philosopher *philo, char *state);

// Monitoring functions
int			check_death(t_philosopher *philo);
void		monitor_philosophers(t_program *program,
				t_philosopher *philosophers);

// Cleanup functions
void		cleanup_mutexes(t_program *program);
void		cleanup_program(t_program *program);

// Utility functions
int			ft_atoi(const char *str);
int			count_2d_char_array_rows(char **arr);
int			only_numbers_check(const char *str);
int			argument_validation(char **argv);
void		print_state(t_philosopher *philo, char *state);

//philo utils 
void		take_forks(t_philosopher *philo);
void		eat(t_philosopher *philo);
int			simulation_should_stop(t_philosopher *philo);
void		sleeping(t_philosopher *philo);
void		thinking(t_philosopher *philo);

#endif