/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:07:20 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/16 14:37:36 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct		s_var
{
	int					num;
	pthread_mutex_t		*m_print;
}t_var;

void	*ft_lock(void *var);
void	*ft_one_repeat(void *var);

int	main(void)
{
	pthread_mutex_t	m_print;
	pthread_t		pid[2];

	pthread_mutex_init(&m_print, NULL);
	pthread_create(&pid[0], NULL, ft_lock, &m_print);
	pthread_create(&pid[1], NULL, ft_one_repeat, &m_print);
	usleep(3000000);
	pthread_mutex_unlock(&m_print);
	usleep(3000000);
	return (0);
}

void	*ft_lock(void *var)
{
	pthread_mutex_t	*m_print;
	// pthread_mutex_t	m_print;

	m_print = (pthread_mutex_t *)var;
	// pthread_mutex_init(&m_print, NULL);
	pthread_mutex_lock(m_print);
	while (1)
	{
		write(1, "1\n", 2);
		usleep(10000);
	}
	return (NULL);
}

void	*ft_one_repeat(void *var)
{
	pthread_mutex_t	*m_print;
	
	// pthread_mutex_lock(&m_print);
	m_print = (pthread_mutex_t *)var;
	pthread_mutex_lock(m_print);
	while (1)
	{
		write(1, "2\n", 2);
		usleep(10000);
	}
}
