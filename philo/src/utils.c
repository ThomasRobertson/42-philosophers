/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:52:17 by troberts          #+#    #+#             */
/*   Updated: 2023/04/09 21:19:21 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	display_error_message(int fd, char *str, int return_code)
{
	int	len;

	if (str == NULL)
		return (return_code);
	len = 0;
	while (str[len])
		len++;
	write(fd, str, len);
	return (return_code);
}
