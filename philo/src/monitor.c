/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:52:57 by troberts          #+#    #+#             */
/*   Updated: 2023/01/27 21:44:20 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_simulation(t_philo philo)
{
	if (philo.common.nbr_meals_to_eat != -1 && philo.common.nbr_meals_to_eat == philo.nbr_meals_eaten)
		return (NO_MORE_MEALS);
	if (philo.time_of_last_meal != -1 && get_time() - philo.time_of_last_meal > \
												philo.common.time.time_to_die)
		return (DEAD_PHILO);
	return (DONT_STOP);
}

pthread_t	launch_monitor(t_philo *philo_struct, t_common common)
{
	t_monitor	monitor_args;
	pthread_t	monitor_id;

	monitor_args.common = common;
	monitor_args.philo_struct = philo_struct;
	pthread_create(&monitor_id, NULL, monitor, &monitor_args);
	return (monitor_id);
}

void	*monitor(void *data)
{
	t_monitor	*monitor;
	t_philo		*philo_struct;
	int			i;
	int			stop_simulation_return;

	monitor = (t_monitor *)data;
	philo_struct = monitor->philo_struct;
	while (!*(monitor->common.is_dead))
	{
		i = 0;
		while (i < monitor->common.nbr_philosophers)
		{
			stop_simulation_return = stop_simulation(philo_struct[i]);
			if (stop_simulation_return == DEAD_PHILO)
			{
				*(monitor->common.is_dead) = 1;
				printf("%d %d died", \
					get_time() - philo_struct[i].common.time.start_time, \
						philo_struct[i].philo_id);
				return (NULL);
			}
			else if (stop_simulation_return == NO_MORE_MEALS)
				return (NULL);
			else if (stop_simulation_return == DONT_STOP)
				i++;
		}
		usleep(1000);
	}
	return (NULL);
}