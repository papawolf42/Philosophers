/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 00:25:06 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/06 19:31:08 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_dining(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	pthread_mutex_lock(&philo->common->m_enter);
	philo->common->num_entered++;
	printf("%d/%d philo's thread had started\n", philo->index,
		philo->common->num_entered);
	pthread_mutex_unlock(&philo->common->m_enter);
	while (philo->common->flag_all_entered == false)
		usleep(10);
	philo->time_last_eat = philo->common->time_start;
	while (1)
	{
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
}

void	ft_eating(t_philo *philo)
{
	philo->state = forking;
	pthread_mutex_lock(&(philo->fork[philo->lfork]));
	ft_print_state(philo);
	pthread_mutex_lock(&(philo->fork[philo->rfork]));
	ft_print_state(philo);
	philo->time_last_eat = ft_time();
	philo->state = eating;
	ft_print_state(philo);
	ft_yousleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&(philo->fork[philo->rfork]));
	pthread_mutex_unlock(&(philo->fork[philo->lfork]));
}

void	ft_sleeping(t_philo *philo)
{
	philo->state = sleeping;
	ft_print_state(philo);
	ft_yousleep(philo->info->time_to_sleep);
}

void	ft_thinking(t_philo *philo)
{
	philo->state = thinking;
	ft_print_state(philo);
}

void	ft_yousleep(long time)
{
	long	target;

	target = time + ft_time();
	while (target > ft_time())
		usleep(1000);
}
