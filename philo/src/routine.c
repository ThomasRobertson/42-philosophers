/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 02:13:20 by troberts          #+#    #+#             */
/*   Updated: 2023/01/27 21:54:46 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo data)
{
	printf("%d %d is sleeping", get_time_since_start(data.common), \
																data.philo_id);
	usleep(data.common.time.time_to_sleep * 1000);
}

int	philo_eat(t_philo *data)
{
	if (data->fork_left->fork_is_used)
		return (RETURN_FAILURE);
	if (pthread_mutex_lock(&(data->fork_left->fork)) != RETURN_SUCCESS)
		giving_up();
	data->fork_left->fork_is_used = true;
	if (data->fork_right->fork_is_used)
	{
		if (pthread_mutex_unlock(&(data->fork_left->fork)) != RETURN_SUCCESS)
			giving_up();
		return (RETURN_FAILURE);
	}
	if (pthread_mutex_lock(&(data->fork_right->fork)) != RETURN_SUCCESS)
		giving_up();
	data->fork_right->fork_is_used = true;
	printf("%d %d has taken a fork", get_time_since_start(data->common), \
																data->philo_id);
	printf("%d %d has taken a fork", get_time_since_start(data->common), \
																data->philo_id);
	printf("%d %d is eating", get_time_since_start(data->common), data->philo_id);
	usleep(data->common.time.time_to_eat * 1000);
	data->time_of_last_meal = get_time_since_start(data->common);
	data->fork_left->fork_is_used = false;
	data->fork_right->fork_is_used = false;
	if (pthread_mutex_unlock(&(data->fork_left->fork)) != RETURN_SUCCESS && \
			pthread_mutex_unlock(&(data->fork_right->fork)) != RETURN_SUCCESS)
		giving_up();
	return (RETURN_SUCCESS);
}

void	philo_think(t_philo data)
{
	int	time_to_think;

	time_to_think = (data.common.time.time_to_die - \
		(get_time_since_start(data.common) - data.time_of_last_meal) - \
			data.common.time.time_to_eat) / 2;
	if (time_to_think < 0)
		return ;
	printf("%d %d is thinking", get_time_since_start(data.common), \
																data.philo_id);
	usleep(time_to_think * 1000);
}

void	think_and_eat(t_philo *data)
{
	while (philo_eat(data) != RETURN_SUCCESS && !*(data->common.is_dead))
		philo_think(*data);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (!*(philo->common.is_dead) && philo->common.nbr_meals_to_eat == \
													philo->nbr_meals_eaten)
	{
		think_and_eat(philo);
		philo_sleep(*philo);
	}
	return (NULL);
}
