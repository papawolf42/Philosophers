/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 14:31:39 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/23 00:04:18 by gunkim           ###   ########.fr       */
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
	usleep(common->time_to_die * 1000);
	ft_loop(philo, common);
	ft_join_thread(philo, common);
}

void	ft_loop(t_philo *philo, t_common *common)
{
	int		i;

	while (1)
	{
		if (common->flag_died
			|| common->count_full == common->num_of_philos)
			return ;
		i = -1;
		while (++i < common->num_of_philos)
		{
			pthread_mutex_lock(&common->m_print);
			if (philo[i].time_last_eat + common->time_to_die < ft_time())
			{
				common->flag_died = true;
				ft_putstr_state(STR_DIED, died, ft_time() - common->time_start,
					philo[i].num);
				pthread_mutex_unlock(&common->m_print);
				return ;
			}
			pthread_mutex_unlock(&common->m_print);
			usleep(1);
		}
		usleep(common->time_delay);
	}
}

void	ft_join_thread(t_philo *philo, t_common *common)
{
	(void)philo;
	while (common->count_entered != 0)
		usleep(common->time_delay);
	write(1, "end\n", 4);
}

void	ft_ending(t_philo *philo)
{
	// ft_putnbr(philo->num);
	// write(1, "\n", 1);
	pthread_mutex_lock(&philo->common->m_enter);
	philo->common->count_entered--;
	pthread_mutex_unlock(&philo->common->m_enter);
}
