/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 02:13:20 by troberts          #+#    #+#             */
/*   Updated: 2023/02/05 19:12:48 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_sleep(t_philo data)
{
	sem_wait(data.output_lock);
	printf("%d %d is sleeping\n", get_time_since_start(data.common),
		data.philo_id);
	sem_post(data.output_lock);
	usleep(data.common.time.time_to_sleep * 1000);
}

int	philo_eat(t_philo data)
{
	pthread_mutex_lock(&(data->fork_right->fork));
	if (data->fork_right->fork_is_used)
	{
		pthread_mutex_unlock(&(data->fork_right->fork));
		usleep(SMALL_WAIT);
		return (RETURN_FAILURE);
	}
	data->fork_right->fork_is_used = true;
	pthread_mutex_unlock(&(data->fork_right->fork));
	pthread_mutex_lock(&(data->fork_left->fork));
	if (data->fork_left->fork_is_used)
	{
		pthread_mutex_lock(&(data->fork_right->fork));
		data->fork_right->fork_is_used = false;
		pthread_mutex_unlock(&(data->fork_left->fork));
		pthread_mutex_unlock(&(data->fork_right->fork));
		usleep(SMALL_WAIT);
		return (RETURN_FAILURE);
	}
	data->fork_left->fork_is_used = true;
	pthread_mutex_unlock(&(data->fork_left->fork));
	pthread_mutex_lock(data->common.output);
	if (!*(data->common.is_dead))
	{
		printf("%d %d has taken a fork\n", get_time_since_start(data->common),
			data->philo_id);
		printf("%d %d has taken a fork\n", get_time_since_start(data->common),
			data->philo_id);
		printf("%d %d is eating\n", get_time_since_start(data->common),
			data->philo_id);
	}
	pthread_mutex_unlock(data->common.output);
	usleep(data->common.time.time_to_eat * 1000);
	pthread_mutex_lock(&(data->update_status));
	data->time_of_last_meal = get_time_since_start(data->common);
	data->nbr_meals_eaten++;
	pthread_mutex_unlock(&(data->update_status));
	pthread_mutex_lock(&(data->fork_left->fork));
	data->fork_left->fork_is_used = false;
	pthread_mutex_unlock(&(data->fork_left->fork));
	pthread_mutex_lock(&(data->fork_right->fork));
	data->fork_right->fork_is_used = false;
	pthread_mutex_unlock(&(data->fork_right->fork));
	return (RETURN_SUCCESS);
}

void	philo_think(t_philo data)
{
	int	time_to_think;

	time_to_think = (data->time_of_last_meal + data->common.time.time_to_die
			- data->common.time.time_to_eat - data->common.time.time_to_sleep
			- get_time_since_start(data->common)) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (pthread_mutex_lock(data->common.output) != RETURN_SUCCESS)
		giving_up();
	if (!*(data->common.is_dead))
		printf("%d %d is thinking\n", get_time_since_start(data->common),
			data->philo_id);
	if (pthread_mutex_unlock(data->common.output) != RETURN_SUCCESS)
		giving_up();
	usleep(time_to_think * 1000);
}

void	think_and_eat(t_philo data)
{
	while (!*(data->common.is_dead) && philo_eat(data) != RETURN_SUCCESS)
		philo_think(data);
}

int	continue_loop(t_philo data)
{
	int	return_code;

	return_code = RETURN_SUCCESS;
	if (*(data->common.is_dead)) // Todo: supervise if dead
		return_code = RETURN_FAILURE;
	if (data->common.nbr_meals_to_eat != -1)
		if (data->nbr_meals_eaten >= data->common.nbr_meals_to_eat)
			return_code = RETURN_FAILURE;
	return (return_code);
}

int	philo_routine(t_philo philo)
{
	if (philo.philo_id % 2 == 0)
		usleep(SMALL_WAIT);
	while (continue_loop(philo) == RETURN_SUCCESS)
	{
		while (philo_eat(philo) != RETURN_SUCCESS)
			(void)philo;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
