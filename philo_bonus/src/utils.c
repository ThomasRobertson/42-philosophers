/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:52:17 by troberts          #+#    #+#             */
/*   Updated: 2023/02/05 02:35:16 by troberts         ###   ########.fr       */
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

int	check_is_dead(t_is_dead	is_dead)
{
	int	return_code;

	pthread_mutex_lock(&(is_dead.lock));
	return_code = *(is_dead.value);
	pthread_mutex_unlock(&(is_dead.lock));
	return (return_code);
}
