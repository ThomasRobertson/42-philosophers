/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:13:56 by troberts          #+#    #+#             */
/*   Updated: 2023/02/05 02:35:37 by troberts         ###   ########.fr       */
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

# define DEAD_PHILO 1
# define DONT_STOP 0
# define NO_MORE_MEALS 2

# define SMALL_WAIT	100

typedef struct s_time_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				start_time;
}					t_time_data;

typedef struct s_is_dead
{
	t_bool			*value;
	pthread_mutex_t	lock;
}					t_is_dead;

typedef struct s_common
{
	t_bool			*is_dead;
	int				nbr_meals_to_eat;
	int				nbr_philo_meals_finished;
	int				nbr_philosophers;
	t_time_data		time;
	pthread_mutex_t	*output;
}					t_common;

typedef sem_t	t_fork;

typedef struct s_philo
{
	pthread_t		tid;
	int				philo_id;
	t_fork			*fork_left;
	t_fork			*fork_right;
	int				time_of_last_meal;
	int				nbr_meals_eaten;
	t_common		common;
	pthread_mutex_t	update_status;
}					t_philo;

typedef struct s_monitor
{
	t_common		common;
	t_philo			*philo_struct;
}					t_monitor;

typedef struct s_main
{
	t_common		common;
	t_bool			is_dead;
	t_fork			*forks;
	t_philo			*philo_struct;
	pthread_t		*pid_threads;
	pthread_mutex_t	output;
	t_monitor		monitor_args;
}					t_main;

// CLEAN
void				clean_philos(t_philo *philos);

// FT_ATOI
int					ft_atoi(const char *str);

// MONITOR
void				*monitor(void *data);
pthread_t			launch_monitor(t_philo *philo_struct, t_common common,
						t_monitor *monitor_args);

// PHILO
pthread_t			*launch_philos(int number_philosophers, t_philo *philos);

// ROUTINE
void				*philo_routine(void *data);

// UTILS
void				giving_up(void);
int					get_time(void);
int					get_time_since_start(t_common common);

#endif