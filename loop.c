/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 14:31:39 by gunkim            #+#    #+#             */
/*   Updated: 2021/08/07 01:37:17 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_loop(t_philo *philo, t_common *common, int i)
{
	while (1)
	{
		if (common->count_full == common->num_of_philos)
			return ;
		i = -1;
		while (++i < common->num_of_philos)
		{
			pthread_mutex_lock(&common->m_print);
			if (common->flag_died)
			{
				pthread_mutex_unlock(&common->m_print);
				return ;
			}
			if (philo[i].time_last_eat + common->time_to_die < ft_time())
			{
				common->flag_died = true;
				ft_putstr_state(STR_DIED, died, common, philo[i].num);
				pthread_mutex_unlock(&common->m_print);
				return ;
			}
			pthread_mutex_unlock(&common->m_print);
			usleep(5);
		}
		usleep(common->time_delay);
	}
}

void	ft_join_thread(t_common *common)
{
	while (common->count_entered != 0)
		usleep(common->time_delay);
}

void	ft_ending(t_philo *philo)
{
	pthread_mutex_lock(&philo->common->m_enter);
	philo->common->count_entered--;
	pthread_mutex_unlock(&philo->common->m_enter);
}
