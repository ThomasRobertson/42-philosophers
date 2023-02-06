/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 02:13:20 by troberts          #+#    #+#             */
/*   Updated: 2023/02/06 15:17:00 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_sleep(t_philo *data)
{
	check_stop_simulation(data);
	sem_wait(data->output_lock);
	printf("%d %d is sleeping\n", get_time_since_start(data->common),
		data->philo_id);
	sem_post(data->output_lock);
	usleep(data->common.time.time_to_sleep * 1000);
}

int	philo_eat(t_philo *data)
{
	check_stop_simulation(data);
	sem_wait(data->forks);
	// int value;
	// sem_getvalue(data->forks, &value);
	// printf("value : %i\n", value);
	sem_wait(data->forks);
	sem_wait(data->output_lock);
	printf("%d %d has taken a fork\n", get_time_since_start(data->common),
		data->philo_id);
	printf("%d %d has taken a fork\n", get_time_since_start(data->common),
		data->philo_id);
	printf("%d %d is eating\n", get_time_since_start(data->common),
		data->philo_id);
	sem_post(data->output_lock);
	data->time_of_last_meal = get_time_since_start(data->common);
	usleep(data->common.time.time_to_eat * 1000);
	sem_post(data->forks);
	sem_post(data->forks);
	data->nbr_meals_eaten++;
	return (RETURN_SUCCESS);
}

void	philo_think(t_philo *data)
{
	int	time_to_think;

	check_stop_simulation(data);
	time_to_think = (data->time_of_last_meal + data->common.time.time_to_die
			- data->common.time.time_to_sleep
			- get_time_since_start(data->common)) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	sem_wait(data->output_lock);
	printf("%d %d is thinking\n", get_time_since_start(data->common),
		data->philo_id);
	sem_post(data->output_lock);
	usleep(time_to_think * 1000);
}

void	routine_one_philo(t_philo philo)
{
	sem_wait(philo.forks);
	printf("%d %d has taken a fork\n", get_time_since_start(philo.common),
		philo.philo_id);
	usleep(philo.common.time.time_to_die * 1000);
	printf("%d %d died\n", get_time_since_start(philo.common),
		philo.philo_id);
	clean_philos(philo, philo.philos_pid);
	exit (DEAD_PHILO);
}

void	philo_routine(t_philo philo)
{
	sem_wait(philo.output_lock);
	printf("%d %d is thinking\n", get_time_since_start(philo.common),
		philo.philo_id);
	sem_post(philo.output_lock);
	if (philo.philo_id % 2 == 0)
		philo_think(&philo);
	while (1)
	{
		philo_eat(&philo);
		philo_sleep(&philo);
		philo_think(&philo);
	}
}
