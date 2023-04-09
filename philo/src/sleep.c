/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:25:35 by troberts          #+#    #+#             */
/*   Updated: 2023/04/09 21:05:15 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(unsigned int time, t_philo *data)
{
	int	start_time;
	int	target_time_ms;
	int	i;

/* 	usleep(time);
	return ; */
	i = 0;
	start_time = get_time_since_start(data->common);
	target_time_ms = time / 1000;
	if (target_time_ms <= 0)
		return ;
	while (get_time_since_start(data->common) - start_time < target_time_ms)
	{
		if (i == (1000 / SMALL_SLEEP * 1000))
		{
			i = 0;
			pthread_mutex_lock(data->common.output);
			if (*(data->common.is_dead))
			{
				pthread_mutex_unlock(data->common.output);
				return ;
			}
			pthread_mutex_unlock(data->common.output);
		}
		usleep(SMALL_SLEEP);
 		if (data->common.nbr_philosophers < 100)
			usleep(SMALL_SLEEP);
		else
			usleep(LONG_SLEEP);
		i++;
	}
}
