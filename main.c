/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:45:23 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/12 19:06:56 by gunkim           ###   ########.fr       */
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
	else if (argc == 5)
		info->num_of_time_each_philo_must_eat = -1;
}

t_error	ft_set_up_dining(t_info *info)
{
	t_philo			*philo;
	pthread_mutex_t	*fork;
	t_common		common;

	if (ft_alloc_vars(&philo, &fork, info->num_of_philos) != no_error)
		return (err_malloc_fail);
	ft_init_common(info, &common);
	ft_init_vars(info, philo, fork, &common);
	ft_enter_dining_room(info, philo, &common);
	return (no_error);
}