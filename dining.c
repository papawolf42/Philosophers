/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 00:25:06 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/14 20:44:06 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_dining(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	ft_sitting(philo);
	while (1)
	{
		if (ft_eating(philo) == FULL)
			break ;
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	pthread_mutex_lock(&philo->common->m_full);
	pthread_mutex_lock(&philo->common->m_print);
	philo->common->count_full++;
	ft_putstr("philo ", 6);
	ft_putnbr(philo->num);
	ft_putstr("\n", 1);
	pthread_mutex_unlock(&philo->common->m_print);
	pthread_mutex_unlock(&philo->common->m_full);
	return (NULL);
}

void	ft_sitting(t_philo *philo)
{
	pthread_mutex_lock(&philo->common->m_enter);
	philo->common->count_entered++;
	pthread_mutex_unlock(&philo->common->m_enter);
	while (philo->common->flag_all_entered != true)
		usleep(philo->common->time_delay);
	philo->time_last_eat = philo->common->time_start;
	if (philo->num % 2 == 0)
		ft_sleep(philo, philo->info->time_to_eat);
}

int	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork[philo->rfork]));
	ft_print_state(philo, forking);
	pthread_mutex_lock(&(philo->fork[philo->lfork]));
	ft_print_state(philo, forking);
	philo->time_last_eat = ft_time();
	ft_print_state(philo, eating);
	ft_sleep(philo, philo->info->time_to_eat);
	pthread_mutex_unlock(&(philo->fork[philo->rfork]));
	pthread_mutex_unlock(&(philo->fork[philo->lfork]));
	if (++philo->times_eat == philo->info->num_of_time_each_philo_must_eat)
		return (FULL);
	return (HUNGRY);
}

void	ft_sleeping(t_philo *philo)
{
	ft_print_state(philo, sleeping);
	ft_sleep(philo, philo->info->time_to_sleep);
}

void	ft_thinking(t_philo *philo)
{
	ft_print_state(philo, thinking);
}
