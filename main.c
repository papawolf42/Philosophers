/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:45:23 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/03 02:00:34 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
argv[0]: program name
argv[1]: number_of_philosophers
argv[2]: time_to_die
argv[3]: time_to_eat
argv[4]: time_to_sleep
argv[5]: [number_of_times_each_philosopher_must_eat]
*/
int	main(int argc, char *argv[])
{
	t_info	info;

	if (argc != 5 && argc != 6)
		return (0);
	ft_parse_info(argc, argv, &info);
	ft_set_up_dining(&info);
	return (0);
}

void	ft_parse_info(int argc, char *argv[], t_info *info)
{
	info->num_of_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_of_time_each_philo_must_eat = ft_atoi(argv[5]);
}
