/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:45:25 by troberts          #+#    #+#             */
/*   Updated: 2023/02/05 21:27:26 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_philos(t_philo philo)
{
	sem_close(philo.forks);
	sem_unlink(SEM_NAME_FORK);
	sem_close(philo.output_lock);
	sem_unlink(SEM_NAME_OUTPUT);
}
