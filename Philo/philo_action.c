/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 09:56:52 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/04/20 13:16:28 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_philo *philo)
{
	if ((get_time() - philo->last_meal) > philo->args->time_to_die)
	{
		pthread_mutex_lock(&philo->args->dead_lock);
		if (philo->args->dead == 1)
		{
			print_action(philo, "died");
			philo->args->dead = 0;
		}
		pthread_mutex_unlock(&philo->args->dead_lock);
		return (0);
	}
	return (1);
}
void	print_action(t_philo *philo, char *msg)
{
	size_t time;

	pthread_mutex_lock(&philo->args->print_m);
	if (death(philo->args))
	{
		time = get_time() - philo->args->start_time;
		printf("%zu %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->args->print_m);
}

void	sleeping(t_philo *philo)
{
	print_action(philo, "is sleeping");
	my_sleep(philo->args->time_to_sleep);
}

void	eating(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->meals_lock);
	my_sleep(philo->args->time_to_eat);
	philo->last_meal = get_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->meals_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
