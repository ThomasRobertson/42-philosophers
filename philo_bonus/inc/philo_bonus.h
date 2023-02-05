/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:13:56 by troberts          #+#    #+#             */
/*   Updated: 2023/02/05 22:14:52 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "define.h"
//# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define DEAD_PHILO 1
# define DONT_STOP 0
# define NO_MORE_MEALS 2

# define SMALL_WAIT	100

# define SEM_NAME_FORK "/philo_sem_42"
# define SEM_NAME_OUTPUT "/philo_sem_output"

typedef struct s_time_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				start_time;
}					t_time_data;

// typedef struct s_is_dead
// {
// 	t_bool			*value;
// 	pthread_mutex_t	lock;
// }					t_is_dead;

typedef struct s_common
{
	t_bool			*is_dead;
	int				nbr_meals_to_eat;
	int				nbr_philo_meals_finished;
	int				nbr_philosophers;
	t_time_data		time;
}					t_common;

// typedef sem_t	t_fork;

typedef struct s_philo
{
	pid_t			tid;
	int				philo_id;
	int				time_of_last_meal;
	int				nbr_meals_eaten;
	sem_t			*forks;
	t_common		common;
	sem_t			*output_lock;
}					t_philo;

// typedef struct s_monitor
// {
// 	t_common		common;
// 	t_philo			*philo_struct;
// }					t_monitor;

// typedef struct s_main
// {
// 	t_common		common;
// 	t_bool			is_dead;
// 	t_fork			*forks;
// 	t_philo			*philo_struct;
// 	pthread_t		*pid_threads;
// 	pthread_mutex_t	output;
// 	t_monitor		monitor_args;
// }					t_main;

// CLEAN
void				clean_philos(t_philo philo);

// FT_ATOI
int					ft_atoi(const char *str);

// MONITOR
// void				*monitor(void *data);
// pthread_t			launch_monitor(t_philo *philo_struct, t_common common,
// 						t_monitor *monitor_args);

// PHILO
pid_t				*launch_philos(t_philo philo);

// ROUTINE
void				philo_routine(t_philo philo);

// UTILS
void				giving_up(void);
int					get_time(void);
int					get_time_since_start(t_common common);
void				check_stop_simulation(t_philo *philo);

#endif