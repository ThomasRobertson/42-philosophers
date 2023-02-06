/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:16:35 by troberts          #+#    #+#             */
/*   Updated: 2023/02/06 15:40:48 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_semaphors(int number_philosophers, sem_t **forks, sem_t **output)
{
	sem_unlink(SEM_NAME_FORK);
	*forks = sem_open(SEM_NAME_FORK, O_CREAT, S_IRUSR | S_IWUSR,
			number_philosophers);
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

int	check_args(char	*str)
{
	int	nbr;
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			exit(EXIT_FAILURE);
		i++;
	}
	nbr = ft_atoi(str);
	if (nbr < 0)
	{
		printf("Error: arg < 0.\n");
		exit(EXIT_FAILURE);
	}
	return (nbr);
}

t_philo	create_philo_struct(int ac, char **av)
{
	t_philo		philo;
	t_common	common;
	t_time_data	time_data;

	common.nbr_philosophers = check_args(av[1]);
	time_data.time_to_die = check_args(av[2]);
	time_data.time_to_eat = check_args(av[3]);
	time_data.time_to_sleep = check_args(av[4]);
	if (ac == 6)
		common.nbr_meals_to_eat = check_args(av[5]);
	else
		common.nbr_meals_to_eat = -1;
	common.nbr_philo_meals_finished = 0;
	philo.nbr_meals_eaten = 0;
	philo.time_of_last_meal = -1;
	create_semaphors(common.nbr_philosophers, &philo.forks, &philo.output_lock);
	time_data.start_time = get_time();
	common.time = time_data;
	philo.common = common;
	return (philo);
}

void	wait_child(t_philo philo_struct, pid_t *philos_pid)
{
	int			wstatus;
	int			i;

	i = 0;
	while (i < philo_struct.common.nbr_philosophers)
	{
		waitpid(-1, &wstatus, 0);
		if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == DEAD_PHILO)
		{
			i = 0;
			while (i < philo_struct.common.nbr_philosophers)
			{
				kill(philos_pid[i], SIGKILL);
				i++;
			}
			return ;
		}
		i++;
	}
	return ;
}

int	main(int ac, char **av)
{
	pid_t		*philos_pid;
	t_philo		philo_struct;

	if (ac < 5 || ac > 6)
		return (EXIT_FAILURE);
	philo_struct = create_philo_struct(ac, av);
	philos_pid = launch_philos(philo_struct);
	wait_child(philo_struct, philos_pid);
	clean_philos(philo_struct, philos_pid);
	unlink_sem();
	return (EXIT_SUCCESS);
}
