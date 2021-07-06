/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 12:53:33 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/06 19:05:26 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_state(t_philo *philo)
{
	long	now;

	pthread_mutex_lock(&(philo->common->m_print));
	now = ft_time() - philo->common->time_start;
	if (philo->state == forking)
		printf(STR_FORK, now, philo->index, ANSI_YELLOW);
	else if (philo->state == eating)
		printf(STR_EAT, now, philo->index, ANSI_GREEN);
	else if (philo->state == sleeping)
		printf(STR_SLEEP, now, philo->index, ANSI_CYAN);
	else if (philo->state == thinking)
		printf(STR_THINK, now, philo->index, ANSI_MAGENTA);
	pthread_mutex_unlock(&(philo->common->m_print));
}
