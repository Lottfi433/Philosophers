/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:02:51 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/04/23 09:34:16 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_creation(t_args *args)
{
	int			i;
	pthread_t	monit;
	pthread_t	*w;

	i = 0;
	philo_int(args);
	while (i < args->philos_nb)
	{
		w = &args->philo[i].thread;
		if (pthread_create(w, NULL, &routine, &args->philo[i]) != 0)
			error(args);
		i++;
	}
	if (pthread_create(&monit, NULL, &monitoring, args) != 0)
		error(args);
	i = 0;
	while (i < args->philos_nb)
	{
		pthread_join(args->philo[i].thread, NULL);
		i++;
	}
	pthread_join(monit, NULL);
}

void	philo_int(t_args *args)
{
	int				i;

	i = 0;
	while (i < args->philos_nb)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&args->print_m, NULL);
	pthread_mutex_init(&args->dead_lock, NULL);
	i = 0;
	while (i < args->philos_nb)
	{
		args->philo[i].id = i + 1;
		args->philo[i].last_meal = get_time();
		args->philo[i].meals = 0;
		args->philo[i].args = args;
		args->philo[i].left_fork = &args->forks[i];
		args->philo[i].right_fork = &args->forks[(i + 1) % args->philos_nb];
		pthread_mutex_init(&args->philo[i].meals_lock, NULL);
		i++;
	}
}

void	args_parsing(char **av, t_args *args)
{
	args->philos_nb = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->eat_times = ft_atoi(av[5]);
	args->start_time = get_time();
	args->dead = 1;
}

void	main_helper(t_args *args, char **av)
{
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0
		|| ft_atoi(av[4]) <= 0 || ft_atoi(av[5]) < 0)
		error(args);
}

int	main(int ac, char **av)
{
	t_args	*args;

	args = malloc (sizeof(t_args));
	if (args == NULL)
		error(args);
	if (ac == 6 || ac == 5)
	{
		args_parsing(av, args);
		main_helper(args, av);
		thread_creation(args);
	}
	else
		write(2, "bad usage!", 10);
}
