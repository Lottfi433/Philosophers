/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:02:33 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/04/17 10:50:11 by yazlaigi         ###   ########.fr       */
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
	long long		last_meal;
	int				meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meals_lock;
	t_args	*args;
}	t_philo;

typedef struct s_args
{
	int	philos_nb;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_times;
	t_philo philo[200];
}	t_args;


int			ft_atoi(char *str);
long long	get_time(void);
void		args_parsing(char **av, t_args *args);
void		error(t_args *args);
void		thread_creation(t_args *args);
void		*routine(void *args);
void		*monitoring(void *arg);
#endif