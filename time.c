/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:17:20 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/06 19:05:26 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time(void)
{
	struct timeval	timeval;
	long			ms;

	gettimeofday(&timeval, NULL);
	ms = timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	return (ms);
}

// long	ft_time(t_philo *philo)
// {
// 	if (philo->state == eating)
// 		return (philo->time_last_eat - philo->common->time_start);
// 	else if (philo->state != eating)
// 		return (philo->time_temp - philo->common->time_start);
// 	return (0);
// }
