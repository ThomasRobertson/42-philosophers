/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:25:35 by troberts          #+#    #+#             */
/*   Updated: 2023/04/03 02:43:44 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(useconds_t time, t_philo *data)
{
	useconds_t	time_to_sleep;
	t_bool		is_dead;

	while (time > 0)
	{
		if (time >= USLEEP_MAX_CYCLE_LENGHT)
			time_to_sleep = USLEEP_MAX_CYCLE_LENGHT;
		else
			time_to_sleep = time;
		time -= time_to_sleep;
		pthread_mutex_lock(data->common.output);
		is_dead = *(data->common.is_dead);
		pthread_mutex_unlock(data->common.output);
		if (!is_dead)
			usleep(time_to_sleep);
		else
			break ;
	}
}
