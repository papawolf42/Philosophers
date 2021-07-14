/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:17:20 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/14 20:21:02 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

void	ft_sleep(t_philo *philo, long time)
{
	long	target;
	long	deadline;

	target = time + ft_time();
	deadline = philo->time_last_eat + philo->info->time_to_die;
	usleep(time * 950);
	while (target > ft_time())
		usleep(philo->common->time_delay);
}
