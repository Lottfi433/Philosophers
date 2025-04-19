/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:02:33 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/04/19 12:52:58 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
typedef struct s_args t_args;
typedef struct s_philo t_philo;
typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	size_t		last_meal;
	int				meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meals_lock;
	t_args	*args;
}	t_philo;

typedef struct s_args
{
	int	philos_nb;
	size_t	start_time;
	size_t	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_times;
	int	dead;
	pthread_mutex_t print_m;
	pthread_mutex_t dead_lock;
	pthread_mutex_t	forks[200];
	t_philo philo[200];
}	t_args;

int	death(t_args *args);
int		ft_atoi(char *str);
size_t	get_time(void);
void	args_parsing(char **av, t_args *args);
void	error(t_args *args);
void	thread_creation(t_args *args);
void	*routine(void *args);
void	*monitoring(void *arg);
void	print_action(t_philo *philo, char *msg);
void	eating(t_philo *philo);
int		death_check(t_philo *philo);
void	sleeping(t_philo *philo);
#endif