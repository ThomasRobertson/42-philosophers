/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:52:17 by troberts          #+#    #+#             */
/*   Updated: 2023/02/05 22:30:03 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	giving_up(void)
{
	write(1, "I'm sorry, but I can't do this anymore.\nI'm giving up.\n", 56);
	exit(EXIT_FAILURE);
}

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	get_time_since_start(t_common common)
{
	return (get_time() - common.time.start_time);
}

void	check_stop_simulation(t_philo *philo)
{
	(void)philo;
	int	time_to_usleep;

	// printf("nbr_meals_to_eat %i\nphilo.nbr_meals_eaten %i\n", philo->common.nbr_meals_to_eat, philo->nbr_meals_eaten);
	if (philo->common.nbr_meals_to_eat != -1
		&& philo->nbr_meals_eaten >= philo->common.nbr_meals_to_eat)
		exit(NO_MORE_MEALS);
	if (philo->time_of_last_meal != -1 && get_time_since_start(philo->common)
		- philo->time_of_last_meal >= philo->common.time.time_to_die)
	{
		time_to_usleep = philo->time_of_last_meal
			+ philo->common.time.time_to_die
			- get_time_since_start(philo->common);
		if (time_to_usleep < 0)
			time_to_usleep = 0;
		usleep(time_to_usleep * 1000);
		sem_wait(philo->output_lock);
		printf("%d %d died\n", get_time_since_start(philo->common),
			philo->philo_id);
		exit(DEAD_PHILO);
	}
	// printf("I'm returning.\n");
	return ;
}
