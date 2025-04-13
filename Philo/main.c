/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasserlotfi <yasserlotfi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:02:51 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/04/13 13:07:04 by yasserlotfi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	args_parsing(char **av, t_args *args)
{
	args->philos_nb = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->eat_times = ft_atoi(av[5]);
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0
		|| ft_atoi(av[4]) <= 0 || ft_atoi(av[5]) <= 0)
		return (-1);
	return (1);
}

void main_helper(t_args **args, t_philo	**philo, char **av)
{
	*args = malloc (sizeof(t_args));
	if (*args == NULL)
		error(*args);
	*philo = malloc (sizeof(t_philo) * (*args)->philos_nb);
	if (*philo == NULL)
		error(*philo);
	if (args_parsing(av, *args) == -1)
		error(*args);
}
int	main(int ac, char **av)
{
	t_args	*args;
	t_philo	*philo;

	if (ac == 6)
	{
		main_helper(&args, &philo, av);
	}
	else
		write(2, "bad usage!", 10);
}
