/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:45:25 by troberts          #+#    #+#             */
/*   Updated: 2023/02/06 00:46:26 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_philos(t_philo *philos, pthread_t *threads_pid, t_fork *forks)
{
	free(philos);
	free(threads_pid);
	free(forks);
}
