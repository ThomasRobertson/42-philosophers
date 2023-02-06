/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:45:25 by troberts          #+#    #+#             */
/*   Updated: 2023/02/06 01:17:21 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_philos(t_philo philo, pid_t *philos_pid)
{
	sem_close(philo.forks);
	sem_close(philo.output_lock);
	free(philos_pid);
}

void	unlink_sem(void)
{
	sem_unlink(SEM_NAME_FORK);
	sem_unlink(SEM_NAME_OUTPUT);
}
