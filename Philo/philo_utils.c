/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasserlotfi <yasserlotfi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:02:19 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/04/16 12:46:27 by yasserlotfi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_int(t_args *args)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc (args->philos_nb * sizeof(pthread_mutex_t));
	if (!forks)
		error(args);
	while (i < args->philos_nb)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < args->philos_nb)
	{
		args->philo[i].id = i;
		args->philo[i].last_meal = get_time();
		args->philo[i].meals = 0;
		args->philo[i].args = args;
		args->philo[i].left_fork = &forks[i];
		args->philo[i].right_fork = &forks[(i + 1) % args->philos_nb];
		i++;
	}
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%lld %d Takes left fork.\n", get_time(), philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%lld %d Takes right fork.\n", get_time(), philo->id);
		philo->last_meal = get_time();
		philo->meals++;
		printf("%lld %d is eating\n", get_time(), philo->id);
		usleep(philo->args->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("%lld %d release both forks\n", get_time(), philo->id);
		printf("%lld %d is sleeping\n", get_time(), philo->id);
		usleep(philo->args->time_to_sleep * 1000);
		printf("%lld %d is thinking\n", get_time(), philo->id);
	}
	return (NULL);
}

void	*monitoring(void *arg)
{
	t_args	*args;
	int		i;

	args = (t_args *)arg;
	while (1)
	{
		i = 0;
		while (i < args->philos_nb)
		{
			if (get_time() - args->philo[i].last_meal > args->time_to_die)
			{
				printf("%lld %d died\n", get_time(), args->philo[i].id);
				exit(0);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	thread_creation(t_args *args)
{
	int i = 0;
	pthread_t	monit;

	philo_int(args);
	while (i < args->philos_nb)
	{
		if (pthread_create(&args->philo[i].thread, NULL, &routine, &args->philo[i]) != 0)
			error(args);
		usleep(100);
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
