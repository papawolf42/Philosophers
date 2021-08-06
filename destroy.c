/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 01:12:07 by gunkim            #+#    #+#             */
/*   Updated: 2021/08/07 01:21:38 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex(t_philo *philo, t_common *common)
{
	int	i;

	i = 0;
	while (i < common->num_of_philos)
	{
		pthread_mutex_destroy(&philo->m_fork[i]);
		i++;
	}
	pthread_mutex_destroy(&common->m_enter);
	pthread_mutex_destroy(&common->m_print);
}

void	ft_destroy_allocated(t_philo *philo)
{
	free(philo->fork);
	free(philo);
}
