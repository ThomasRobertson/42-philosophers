/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:56:20 by troberts          #+#    #+#             */
/*   Updated: 2023/02/06 00:50:55 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_t	create_one_philo(t_philo *args)
{
	pthread_t	thread_id;

	pthread_create(&thread_id, NULL, &philo_routine, args);
	return (thread_id);
}

pthread_t	*launch_philos(int number_philosophers, t_philo *philos)
{
	pthread_t	*philos_pid;
	int			i;

	if (philos == NULL)
		return (NULL);
	philos_pid = malloc(sizeof(*philos_pid) * (number_philosophers + 1));
	if (philos_pid == NULL)
	{
		printf("Error: malloc() failed");
		return (NULL);
	}
	i = 0;
	while (i < number_philosophers)
	{
		philos_pid[i] = create_one_philo(&philos[i]);
		i++;
	}
	return (philos_pid);
}
