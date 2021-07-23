/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 12:53:33 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/22 22:24:13 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_state(t_philo *philo, t_state state)
{
	long	now;

	if (ft_is_dead(philo))
		return ;
	pthread_mutex_lock(&(philo->common->m_print));
	if (philo->common->flag_died)
	{
		pthread_mutex_unlock(&(philo->common->m_print));
		return ;
	}
	now = ft_time() - philo->common->time_start;
	if (state == forking)
		ft_putstr_state(STR_FORK, state, now, philo->num);
	else if (state == eating)
		ft_putstr_state(STR_EAT, state, now, philo->num);
	else if (state == sleeping)
		ft_putstr_state(STR_SLEEP, state, now, philo->num);
	else if (state == thinking)
		ft_putstr_state(STR_THINK, state, now, philo->num);
	pthread_mutex_unlock(&(philo->common->m_print));
}

void	ft_putstr_state(char *str, t_state state, long now, int philo_num)
{
	ft_putnbr_ms(now);
	ft_putstr("ms philo ", 9);
	ft_putnbr(philo_num);
	ft_putstr(str, state);
}

void	ft_putstr(char *s, int strlen)
{
	if (!s)
		return ;
	write(STDOUT, s, strlen);
}

int	ft_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->common->m_print));
	if (philo->common->flag_died != 0)
	{
		pthread_mutex_unlock(&(philo->common->m_print));
		return (true);
	}
	if (philo->time_last_eat + philo->common->time_to_die < ft_time())
	{
		write(1, "thread\n", 7);
		ft_putstr_state(STR_DIED, died, ft_time() - philo->common->time_start,
			philo->num);
		philo->common->flag_died = true;
		pthread_mutex_unlock(&(philo->common->m_print));
		return (true);
	}
	pthread_mutex_unlock(&(philo->common->m_print));
	return (false);
}
