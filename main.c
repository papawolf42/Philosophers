/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:45:23 by gunkim            #+#    #+#             */
/*   Updated: 2021/08/28 13:34:18 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo			*philo;
	t_common		common;

	if (argc != 5 && argc != 6)
		return (0);
	if (ft_parse_info(argc, argv, &common) == false)
		return (0);
	if (ft_set_up_dining(&philo, &common) != no_error)
		exit (1);
	ft_enter_dining_room(philo, &common);
	ft_clean_dining_room(philo, &common);
	return (0);
}

int	ft_parse_info(int argc, char *argv[], t_common *common)
{
	common->num_of_philos = ft_atoi(argv[1]);
	common->time_to_die = ft_atoi(argv[2]);
	common->time_to_eat = ft_atoi(argv[3]);
	common->time_to_sleep = ft_atoi(argv[4]);
	if (common->num_of_philos < 0 || common->time_to_die < 0
		|| common->time_to_eat < 0 || common->time_to_sleep < 0)
		return (false);
	if (argc == 6)
		common->num_of_time_each_philo_must_eat = ft_atoi(argv[5]);
	else if (argc == 5)
		common->num_of_time_each_philo_must_eat = -1;
	return (true);
}

t_error	ft_set_up_dining(t_philo **philo, t_common *common)
{
	pthread_mutex_t	*m_fork;
	int				*fork;

	if (ft_alloc_vars(philo, &m_fork, &fork, common->num_of_philos) != no_error)
		return (err_malloc_fail);
	ft_init_common(common, common->num_of_philos);
	ft_init_vars(*philo, m_fork, fork, common);
	return (no_error);
}

void	ft_enter_dining_room(t_philo *philo, t_common *common)
{
	int		i;

	common->flag_all_entered = false;
	i = 0;
	while (i < common->num_of_philos)
	{
		pthread_create(&(philo[i].thread), NULL, ft_dining, &philo[i]);
		pthread_detach(philo[i].thread);
		i++;
	}
	while (common->count_entered != common->num_of_philos)
		usleep(common->time_delay);
	common->time_start = ft_time();
	common->flag_all_entered = true;
	usleep(common->time_to_die * 1000);
	ft_loop(philo, common, 0);
	ft_wait_thread(common);
}

void	ft_clean_dining_room(t_philo *philo, t_common *common)
{
	ft_destroy_mutex(philo, common);
	ft_destroy_allocated(philo);
}
