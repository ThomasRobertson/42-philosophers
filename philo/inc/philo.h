/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:13:56 by troberts          #+#    #+#             */
/*   Updated: 2023/01/27 21:50:46 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# include "define.h"

# define DEAD_PHILO 1
# define DONT_STOP 0
# define NO_MORE_MEALS 2

typedef struct s_time_data {
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	start_time;
}		t_time_data;

typedef struct s_common {
	t_bool		*is_dead;
	int			nbr_meals_to_eat;
	int			nbr_philosophers;
	t_time_data	time;
}				t_common;

typedef struct s_fork {
	pthread_mutex_t	fork;
	t_bool			fork_is_used;
}					t_fork;

typedef struct s_philo {
	pthread_t	tid;
	int			philo_id;
	t_fork		*fork_left;
	t_fork		*fork_right;
	int			time_of_last_meal;
	int			nbr_meals_eaten;
	t_common	common;
}					t_philo;

typedef struct s_monitor {
	t_common	common;
	t_philo		*philo_struct;
}			t_monitor;

// CLEAN
void		clean_philos(t_philo *philos);

// FT_ATOI
int			ft_atoi(const char *str);

// MONITOR
void		*monitor(void *data);

// PHILO
pthread_t	*launch_philos(int number_philosophers, t_philo *philos);

// ROUTINE
void		*philo_routine(void *data);

// UTILS
void		giving_up(void);
int			get_time(void);
int			get_time_since_start(t_common common);

#endif