/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_dining.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 00:00:26 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/06 19:21:00 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_error	ft_set_up_dining(t_info *info)
{
	t_philo			*philo;
	pthread_mutex_t	*fork;
	t_common		common;

	if (ft_alloc_vars(&philo, &fork, info->num_of_philos) != no_error)
		return (err_malloc_fail);
	ft_init_common(&common);
	ft_init_vars(info, philo, fork, &common);
	ft_enter_dining_room(info, philo, &common);
	return (no_error);
}

t_error	ft_alloc_vars(t_philo **philo, pthread_mutex_t **fork, int num)
{
	int				i;

	*philo = (t_philo *)malloc(sizeof(t_philo) * num);
	if (*philo == NULL)
		return (err_malloc_fail);
	*fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	if (*fork == NULL)
		return (err_malloc_fail);
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&(*fork)[i], NULL);
		i++;
	}
	return (no_error);
}

void	ft_init_common(t_common *common)
{
	pthread_mutex_init(&common->m_print, NULL);
	pthread_mutex_init(&common->m_enter, NULL);
	common->num_entered = 0;
	common->flag_all_entered = false;
	common->flag_someone_died = false;
}

void	ft_init_vars(t_info *info, t_philo *philo, pthread_mutex_t *fork,
			t_common *common)
{
	int		i;

	i = 0;
	while (i < info->num_of_philos)
	{
		philo[i].index = i;
		philo[i].num = i + 1;
		philo[i].fork = fork;
		if (i % 2 == 0)
		{
			philo[i].rfork = i;
			philo[i].lfork = (i + info->num_of_philos - 1)
				% info->num_of_philos;
		}
		else if (i % 2 == 1)
		{
			philo[i].rfork = (i + info->num_of_philos - 1)
				% info->num_of_philos;
			philo[i].lfork = i;
		}
		philo[i].info = info;
		philo[i].common = common;
		i++;
	}
}

void	ft_enter_dining_room(t_info *info, t_philo *philo, t_common *common)
{
	int		i;

	common->flag_all_entered = false;
	i = 0;
	while (i < info->num_of_philos)
	{
		pthread_create(&(philo[i].thread), NULL, ft_dining, &philo[i]);
		i++;
	}
	while (common->num_entered != info->num_of_philos)
		usleep(100);
	common->time_start = ft_time();
	common->flag_all_entered = true;
	i = 0;
	while (i < info->num_of_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}
