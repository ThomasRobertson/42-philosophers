/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:21:27 by troberts          #+#    #+#             */
/*   Updated: 2023/02/06 02:44:34 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	continue_loop(t_philo *data)
{
	int	return_code;

	return_code = RETURN_SUCCESS;
	pthread_mutex_lock(&data->update_status);
	if (*(data->common.is_dead))
		return_code = RETURN_FAILURE;
	if (data->common.nbr_meals_to_eat != -1)
		if (data->nbr_meals_eaten >= data->common.nbr_meals_to_eat)
			return_code = RETURN_FAILURE;
	pthread_mutex_unlock(&data->update_status);
	return (return_code);
}

int	take_forks(t_philo *data)
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
	return (RETURN_SUCCESS);
}

void	output_eat(t_philo *data)
{
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
}

void	*routine_one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&(philo->fork_right->fork));
	philo->fork_right->fork_is_used = true;
	pthread_mutex_unlock(&(philo->fork_right->fork));
	printf("%d %d has taken a fork\n", get_time_since_start(philo->common),
		philo->philo_id);
	usleep(philo->common.time.time_to_die * 1000);
	printf("%d %d died\n", get_time_since_start(philo->common),
		philo->philo_id);
	return (NULL);
}
