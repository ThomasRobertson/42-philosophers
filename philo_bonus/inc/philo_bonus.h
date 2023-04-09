/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:13:56 by troberts          #+#    #+#             */
/*   Updated: 2023/04/09 18:58:50 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "define.h"
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
# define MAX_TIME_THINK 2000

# define SEM_NAME_FORK "/philo_sem_42"
# define SEM_NAME_OUTPUT "/philo_sem_output"

typedef struct s_time_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				start_time;
}					t_time_data;

typedef struct s_common
{
	t_bool			*is_dead;
	int				nbr_meals_to_eat;
	int				nbr_philo_meals_finished;
	int				nbr_philosophers;
	t_time_data		time;
}					t_common;

typedef struct s_philo
{
	pid_t			tid;
	int				philo_id;
	int				time_of_last_meal;
	int				nbr_meals_eaten;
	sem_t			*forks;
	t_common		common;
	sem_t			*output_lock;
	pid_t			*philos_pid;
}					t_philo;

// CLEAN
void				clean_philos(t_philo philo, pid_t *philos_pid);
void				unlink_sem(void);

// FT_ATOI
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
// PHILO
pid_t				*launch_philos(t_philo philo);

// ROUTINE
void				philo_routine(t_philo philo);
void				routine_one_philo(t_philo philo);

// UTILS
int					get_time(void);
int					get_time_since_start(t_common common);
void				check_stop_simulation(t_philo *philo);
void				ft_usleep(int time, t_philo *philo);

#endif