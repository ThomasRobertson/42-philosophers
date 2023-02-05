/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:16:35 by troberts          #+#    #+#             */
/*   Updated: 2023/02/05 22:49:28 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_semaphors(int number_philosophers, sem_t **forks, sem_t **output)
{
	sem_unlink(SEM_NAME_FORK);
	*forks = sem_open(SEM_NAME_FORK, O_CREAT, S_IRUSR | S_IWUSR, number_philosophers);
	int sem_value;
	sem_getvalue(*forks, &sem_value); // Remove
	printf("%i\n%i\n",number_philosophers, sem_value);
	if (*forks == SEM_FAILED)
		exit(EXIT_FAILURE);
	sem_unlink(SEM_NAME_OUTPUT);
	*output = sem_open(SEM_NAME_OUTPUT, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (*output == SEM_FAILED)
	{
		sem_close(*forks);
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
	int			wstatus;
	int			i;

	if (ac < 5 || ac > 6)
		return (EXIT_FAILURE);
	philo_struct = create_philo_struct(ac, av);
	philos_pid = launch_philos(philo_struct);
	i = 0;
	while (i < philo_struct.common.nbr_philosophers)
	{
		waitpid(-1, &wstatus, 0);
		if (WIFEXITED(wstatus))
		{
			if (WEXITSTATUS(wstatus) == DEAD_PHILO)
			{
				i = 0;
				while (i < philo_struct.common.nbr_philosophers)
				{
					kill(philos_pid[i], SIGKILL);
					i++;
				}
				break ;
			}
		}
		i++;
	}
	clean_philos(philo_struct);
	return (EXIT_SUCCESS);
}
