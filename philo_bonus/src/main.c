/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:16:35 by troberts          #+#    #+#             */
/*   Updated: 2023/02/05 19:06:43 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_semaphors(int number_philosophers, sem_t **forks, sem_t **output)
{
	sem_t	*forks;

	*forks = sem_open(SEM_NAME_FORK, O_CREAT, S_IRUSR | S_IWUSR, number_philosophers);
	if (*forks == SEM_FAILED)
		exit(EXIT_FAILURE);
	*output = sem_open(SEM_NAME_OUTPUT, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (*output == SEM_FAILED)
	{
		sem_destroy(*forks);
		sem_unlink(SEM_NAME_FORK);
		exit(EXIT_FAILURE);
	}
}

t_philo	create_philo_struct(int ac, char **av)
{
	t_philo		philo;
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
	common.time = time_data;
	common.nbr_philo_meals_finished = 0;
	philo.common = common;
	philo.nbr_meals_eaten = 0;
	philo.time_of_last_meal = -1;
	create_semaphors(common.nbr_philosophers, &philo.forks, &philo.output_lock);
	return (philo);
}

int	main(int ac, char **av)
{
	pid_t		*philos_pid;
	t_philo		philo_struct;

	if (ac < 5 || ac > 6)
		return (EXIT_FAILURE);
	philo_struct = create_philo_struct(ac, av);
	philos_pid = launch_philos(philo_struct);


	main.monitor_args.common = main.common;
	main.monitor_args.philo_struct = main.philo_struct;
	main.pid_threads[main.common.nbr_philosophers]
		= launch_monitor(main.philo_struct, main.common, &main.monitor_args);
	i = 0;
	while (i < main.common.nbr_philosophers)
	{
		pthread_join(main.pid_threads[i], NULL);
		i++;
	}
	pthread_join(main.pid_threads[main.common.nbr_philosophers], NULL);
	return (EXIT_SUCCESS);
}
