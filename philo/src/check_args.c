/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:15:43 by troberts          #+#    #+#             */
/*   Updated: 2023/04/09 21:16:04 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
