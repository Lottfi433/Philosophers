/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:02:19 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/04/20 13:15:52 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	i = 0;
	while (i < args->philos_nb)
	{
		args->philo[i].id = i + 1;
		args->philo[i].last_meal = get_time();
		args->philo[i].meals = 0;
		args->philo[i].args = args;
		args->philo[i].left_fork = &args->forks[i];
		args->philo[i].right_fork = &args->forks[(i + 1) % args->philos_nb];
		i++;
	}
}

int	death(t_args *args)
{
	int	x;

	pthread_mutex_lock(&args->dead_lock);
	x = args->dead;
	pthread_mutex_unlock(&args->dead_lock);
	return (x);
}

void	routine_helper(t_philo	*philo)
{
	int	i;

	i = 0;
	if (philo->args->eat_times != 0)
	{
		while (death(philo->args) && i < philo->args->eat_times)
		{
			eating(philo);
			sleeping(philo);
			print_action(philo, "is thinking");
			i++;
		}
	}
	else
	{
		while (death(philo->args))
		{
			eating(philo);
			sleeping(philo);
			print_action(philo, "is thinking");
		}
	}
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->args->philos_nb == 1)
	{
		printf("%lu %d Takes left Fork\n", get_time() - philo->args->start_time, philo->id);
		my_sleep(philo->args->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(100);
	routine_helper(philo);
	return (NULL);
}

void	*monitoring(void *arg)
{
	t_args	*args;
	int		i;
	int		full_philos;

	args = (t_args *)arg;
	while (death(args))
	{
		full_philos = 0;
		i = 0;
		while (i < args->philos_nb)
		{
			pthread_mutex_lock(&args->philo[i].meals_lock);
			if ((get_time() - args->philo[i].last_meal) >= args->time_to_die)
			{
				printf("%zu %d died\n", (get_time() - args->start_time), args->philo[i].id);
				pthread_mutex_lock(&args->dead_lock);
				args->dead = 0;
				pthread_mutex_unlock(&args->dead_lock);
				pthread_mutex_unlock(&args->philo[i].meals_lock);
				return (NULL);
			}
			if (args->eat_times > 0 && args->philo[i].meals >= args->eat_times)
				full_philos++;
			pthread_mutex_unlock(&args->philo[i].meals_lock);
			i++;
		}
		if (full_philos == args->philos_nb)
			return (NULL);
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
