/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:16:35 by troberts          #+#    #+#             */
/*   Updated: 2023/02/06 01:43:24 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo_struct(t_fork *forks, t_common common)
{
	t_philo			*struct_philo;
	int				i;

	struct_philo = malloc(sizeof(*struct_philo) * common.nbr_philosophers);
	if (struct_philo == NULL)
	{
		printf("Error: malloc() failed");
		return (NULL);
	}
	i = 0;
	while (i < common.nbr_philosophers)
	{
		struct_philo[i].philo_id = i + 1;
		struct_philo[i].fork_left = &forks[i];
		if (struct_philo[i].philo_id == common.nbr_philosophers)
			struct_philo[i].fork_right = &forks[0];
		else
			struct_philo[i].fork_right = &forks[i + 1];
		struct_philo[i].time_of_last_meal = -1;
		struct_philo[i].nbr_meals_eaten = 0;
		struct_philo[i].common = common;
		pthread_mutex_init(&struct_philo[i].update_status, NULL);
		i++;
	}
	return (struct_philo);
}

t_common	fill_args(int ac, char **av, t_bool *is_dead,
		pthread_mutex_t *output)
{
	t_common	common;
	t_time_data	time_data;

	pthread_mutex_init(output, NULL);
	common.output = output;
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
	common.nbr_philo_meals_finished = 0;
	return (common);
}

t_fork	*create_forks(int number_philosophers)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(*forks) * (number_philosophers + 1));
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

void	join_threads(pthread_t *pid_threads, int nbr_philosophers)
{
	int	i;

	i = 0;
	while (i < nbr_philosophers)
	{
		pthread_join(pid_threads[i], NULL);
		i++;
	}
	pthread_join(pid_threads[nbr_philosophers], NULL);
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac < 5 || ac > 6)
		return (EXIT_FAILURE);
	main.is_dead = false;
	main.common = fill_args(ac, av, &main.is_dead, &main.output);
	if (check_args(main.common, ac, av) == RETURN_FAILURE)
		return (EXIT_SUCCESS);
	main.forks = create_forks(main.common.nbr_philosophers);
	if (main.forks == NULL)
		return (EXIT_FAILURE);
	main.philo_struct = create_philo_struct(main.forks, main.common);
	main.pid_threads = launch_philos(main.common.nbr_philosophers,
			main.philo_struct);
	if (main.pid_threads == NULL)
	{
		clean_philos(main.philo_struct, main.pid_threads, main.forks);
		return (EXIT_FAILURE);
	}
	main.pid_threads[main.common.nbr_philosophers]
		= launch_monitor(&main.philo_struct, &main.common, &main.monitor_args);
	join_threads(main.pid_threads, main.common.nbr_philosophers);
	clean_philos(main.philo_struct, main.pid_threads, main.forks);
	return (EXIT_SUCCESS);
}
