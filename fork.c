/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:23:30 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/22 22:51:26 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philo *philo, int idx_fork)
{
	while (!philo->common->flag_died)
	{
		pthread_mutex_lock(&(philo->m_fork[idx_fork]));
		if (philo->fork[idx_fork] == 0)
		{
			philo->fork[idx_fork] = 1;
			pthread_mutex_unlock(&(philo->m_fork[idx_fork]));
			return ;
		}
		pthread_mutex_unlock(&(philo->m_fork[idx_fork]));
		usleep(philo->common->time_delay);
	}
}

void	ft_takedown_fork(t_philo *philo, int idx_fork)
{
	while (!philo->common->flag_died)
	{
		pthread_mutex_lock(&(philo->m_fork[idx_fork]));
		if (philo->fork[idx_fork] != 0)
		{
			philo->fork[idx_fork] = 0;
			pthread_mutex_unlock(&(philo->m_fork[idx_fork]));
			return ;
		}
		pthread_mutex_unlock(&(philo->m_fork[idx_fork]));
		usleep(philo->common->time_delay);
	}
}
