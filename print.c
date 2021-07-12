/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 12:53:33 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/10 23:10:39 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_state(t_philo *philo, t_state state)
{
	long	now;

	pthread_mutex_lock(&(philo->common->m_print));
	now = ft_time() - philo->common->time_start;
	if (state == died)
	{
		ft_putstr_state(STR_DIED, state, now, philo->num);
		philo->common->flag_someone_died = true;
		pthread_mutex_unlock(&philo->common->m_check_die);
		return ;
	}
	else if (state == forking)
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
