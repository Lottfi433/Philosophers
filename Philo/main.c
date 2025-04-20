/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:02:51 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/04/20 13:26:56 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void main_helper(t_args *args, char **av)
{
	 if(ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0
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
