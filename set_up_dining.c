/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_dining.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 00:00:26 by gunkim            #+#    #+#             */
/*   Updated: 2021/08/07 01:17:59 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "philo.h"

t_error	ft_alloc_vars(t_philo **philo, pthread_mutex_t **m_fork,
			int **fork, int num)
{
	int	i;

	*philo = (t_philo *)malloc(sizeof(t_philo) * num);
	if (*philo == NULL)
		return (err_malloc_fail);
	*m_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	if (*m_fork == NULL)
		return (err_malloc_fail);
	*fork = (int *)malloc(sizeof(int) * num);
	if (*fork == NULL)
		return (err_malloc_fail);
	i = 0;
	while (i < num)
		pthread_mutex_init(&(*m_fork)[i++], NULL);
	i = 0;
	while (i < num)
		(*fork)[i++] = 0;
	return (no_error);
}

void	ft_init_common(t_common *common, int num)
{
	common->time_delay = num * 2.3;
	common->count_full = 0;
	common->count_entered = 0;
	common->num_starve = num;
	common->flag_died = false;
	common->flag_all_eaten = false;
	common->flag_all_entered = false;
	pthread_mutex_init(&common->m_enter, NULL);
	pthread_mutex_init(&common->m_print, NULL);
}

void	ft_init_vars(t_philo *philo, pthread_mutex_t *m_fork,
			int *fork, t_common *common)
{
	int		i;

	i = -1;
	while (++i < common->num_of_philos)
		pthread_mutex_init(&(m_fork[i]), NULL);
	i = -1;
	while (++i < common->num_of_philos)
	{
		philo[i].index = i;
		philo[i].num = i + 1;
		philo[i].m_fork = m_fork;
		philo[i].fork = fork;
		philo[i].rfork = i;
		philo[i].lfork = (i + common->num_of_philos - 1)
			% common->num_of_philos;
		philo[i].time_last_eat = LONG_MAX;
		philo[i].times_eat = 0;
		philo[i].common = common;
	}
}
