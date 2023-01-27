/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:16:35 by troberts          #+#    #+#             */
/*   Updated: 2023/01/27 04:21:06 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo_struct(t_fork *forks, t_common common)
{
	t_philo	*struct_philo;
	int		i;

	struct_philo = malloc(sizeof(*struct_philo) * common.nbr_philosophers);
	if (struct_philo == NULL)
	{
		printf("Error: malloc() failed");
		return (NULL);
	}
	i = 0;
	while (i <= common.nbr_philosophers)
	{
		struct_philo[i].philo_id = i + 1;
		struct_philo[i].fork_left = &forks[i];
		if (struct_philo[i].philo_id == common.nbr_philosophers)
			struct_philo[i].fork_left = &forks[0];
		else
			struct_philo[i].fork_right = &forks[i + 1];
		struct_philo[i].time_of_last_meal = -1;
		struct_philo[i].nbr_meals_eaten = 0;
		struct_philo[i].common = common;
		i++;
	}
	return (struct_philo);
}

t_common	fill_args(int ac, char **av, t_bool *is_dead)
{
	t_common	common;
	t_time_data	time_data;

	common.nbr_philosophers = ft_atoi(av[1]);
	time_data.time_to_die = ft_atoi(av[2]);
	time_data.time_to_eat = ft_atoi(av[3]);
	time_data.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		common.nbr_meals_to_eat = ft_atoi(av[5]);
	else
		common.nbr_meals_to_eat = -1;
	time_data.start_time = get_time();
	common.is_dead = is_dead;
	common.time = time_data;
	return (common);
}

t_fork	*create_forks(int number_philosophers)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(*forks) * number_philosophers);
	if (forks == NULL)
	{
		printf("Error: malloc() failed");
		return (NULL);
	}
	i = 0;
	while (i < number_philosophers)
	{
		pthread_mutex_init(&forks[i].fork, NULL);
		forks[i].fork_is_used = false;
		i++;
	}
	return (forks);
}

int	main(int ac, char **av)
{
	pthread_t		*philos;
	t_common		common;
	t_bool			is_dead;
	t_fork			*forks;
	t_philo			*philo_struct;

	if (ac < 5 || ac > 6)
		return (EXIT_FAILURE);
	is_dead = false;
	common = fill_args(ac, av, &is_dead);
	forks = create_forks(common.nbr_philosophers);
	if (forks == NULL)
		return (EXIT_FAILURE);
	philo_struct = create_philo_struct(forks, common);
	if (philo_struct == NULL)
		return (EXIT_FAILURE);
	philos = launch_philos(common.nbr_philosophers, philo_struct);
	(void)philos;
	return (EXIT_SUCCESS);
}
