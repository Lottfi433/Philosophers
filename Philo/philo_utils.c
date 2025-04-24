/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:02:19 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/04/24 10:17:08 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*routine(void *arg)
{
	t_philo	*philo;
	size_t	time;

	philo = (t_philo *)arg;
	if (philo->args->philos_nb == 1)
	{
		time = get_time() - philo->args->start_time;
		pthread_mutex_lock(philo->left_fork);
		printf("%lu %d takes left Fork\n", time, philo->id);
		pthread_mutex_unlock(philo->left_fork);
		my_sleep(philo->args->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	routine_helper(philo);
	return (NULL);
}

void	monitoring_helper(t_args *args, int i)
{
	size_t	x;

	x = get_time() - args->start_time;
	pthread_mutex_lock(&args->dead_lock);
	printf("%zu %d died\n", x, args->philo[i].id);
	args->dead = 0;
	pthread_mutex_unlock(&args->dead_lock);
	pthread_mutex_unlock(&args->philo[i].meals_lock);
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
			if (get_time() - args->philo[i].last_meal >= args->time_to_die)
				return (monitoring_helper(args, i), NULL);
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
