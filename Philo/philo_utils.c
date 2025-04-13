/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasserlotfi <yasserlotfi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:02:19 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/04/13 12:49:46 by yasserlotfi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	r;
	int	s;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if ((str[i] < '0' || str[i] > '9') || s < 0)
			return (0);
		r = r * 10 + (str[i] - 48);
		i++;
	}
	return (r * s);
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

void	*routine(t_philo *philo)
{
	while (1)
	{
		long long	current_time;

		current_time = get_time();
		if (current_time - philo->last_meal > philo->args->time_to_die)
		{
			printf("%lld %d has died.\n", get_time(), philo->id);
			return (NULL);
		}
		pthread_mutex_lock(philo->left_fork);
		printf("%lld %d Takes left fork.\n", get_time(), philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%lld %d Takes right fork.\n", get_time(), philo->id);
		philo->last_meal = get_time();
		philo->meals++;
		printf("%lld %d is eating\n",get_time(), philo->id);
		usleep(philo->args->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("%lld %d release both forks\n", get_time(), philo->id);
		printf("%lld %d is sleeping\n", get_time(), philo->id);
		usleep(philo->args->time_to_sleep * 1000);
		printf("%lld %d is thinking\n", get_time(), philo->id);
	}
}

void	error(t_args *args)
{
	write(1, "Error in args\n", 14);
	if (args != NULL)
		free (args);
	exit(0);
}

void	thread_creation(t_args *args)
{
	int i = 0;
	while (i < args->philos_nb)
	{
		pthread_create(&args->philo[i].thread, NULL, &routine, &args->philo[i]);
		i++;
	}
}