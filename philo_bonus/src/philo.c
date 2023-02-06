/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:56:20 by troberts          #+#    #+#             */
/*   Updated: 2023/02/06 14:59:57 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

pid_t	create_one_philo(t_philo philo)
{
	pid_t	thread_id;

	thread_id = fork();
	if (thread_id == 0)
	{
		if (philo.common.nbr_philosophers == 1)
			routine_one_philo(philo);
		else
			philo_routine(philo);
	}
		
	else
		return (thread_id);
	return (thread_id);
}

pid_t	*launch_philos(t_philo philo)
{
	pid_t	*philos_pid;
	int		nbr_philosophers;
	int		i;

	nbr_philosophers = philo.common.nbr_philosophers;
	philos_pid = malloc(sizeof(*philos_pid) * nbr_philosophers);
	if (philos_pid == NULL)
	{
		printf("Error: malloc() failed");
		return (NULL);
	}
	philo.philos_pid = philos_pid;
	i = 0;
	while (i < nbr_philosophers)
	{
		philo.philo_id = i + 1;
		philos_pid[i] = create_one_philo(philo);
		i++;
	}
	return (philos_pid);
}
