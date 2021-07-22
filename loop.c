/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 14:31:39 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/22 16:35:54 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	// i = -1;
	// while (++i < common->num_of_philos)
	// {
	// 	pthread_join(philo[i].thread, NULL);
	// }
	ft_loop(philo, common);
	usleep(3000000);
}

void	ft_loop(t_philo *philo, t_common *common)
{
	int		i;
	long	moment;

	usleep(common->time_to_die * 1000);
	while (1)
	{
		i = -1;
		while (++i < common->num_of_philos)
		{
			pthread_mutex_lock(&common->m_print);
			if (common->flag_died || common->count_full == common->num_of_philos)
			{
				pthread_mutex_unlock(&common->m_print);
				return ;
			}
			moment = ft_time();
			if (philo[i].time_last_eat + common->time_to_die < moment)
			{
				write(1, "main\n", 5);
				ft_putstr_state(STR_DIED, died, ft_time() - common->time_start,
					philo[i].num);
				exit(1);
			}
			pthread_mutex_unlock(&common->m_print);
			usleep(5);
		}
			usleep(common->time_delay);
	}
}

// int	ft_loop(t_common *info, t_philo *philo, t_common *common)
// {
// 	int		i;
// 	long	moment;

// 	usleep(info->time_to_die * 1000);
// 	while (1)
// 	{
// 		i = 0;
// 		if (common->count_full == info->num_of_philos)
// 			return (FULL);
// 		if (philo->common->)
// 		pthread_mutex_lock(&common->m_check_die);
// 		while (i < info->num_of_philos)
// 		{
// 			moment = ft_time();
// 			if (philo[i].time_last_eat + info->time_to_die < moment
// 				&& common->count_full != info->num_of_philos)
// 			{
// 				ft_putstr_state(STR_DIED, died, ft_time() - common->time_start,
// 					philo[i].num);
// 				exit(1);
// 			}
// 			i++;
// 		}
// 		pthread_mutex_unlock(&common->m_check_die);
// 	}
// }
