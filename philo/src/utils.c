/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:52:17 by troberts          #+#    #+#             */
/*   Updated: 2023/02/06 02:29:59 by troberts         ###   ########.fr       */
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

int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (RETURN_FAILURE);
		i++;
	}
	return (RETURN_SUCCESS);
}

int	check_args(t_common common, int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (is_all_digit(av[i]) == RETURN_FAILURE)
			return (RETURN_FAILURE);
		i++;
	}
	if (common.nbr_philosophers < 1)
		return (RETURN_FAILURE);
	if (common.time.time_to_die < 0)
		return (RETURN_FAILURE);
	if (common.time.time_to_eat < 0)
		return (RETURN_FAILURE);
	if (common.time.time_to_sleep < 0)
		return (RETURN_FAILURE);
	if (common.nbr_meals_to_eat == -1 && ac == 6)
		return (RETURN_FAILURE);
	if (common.nbr_meals_to_eat == 0 && ac == 5)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
