/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 01:53:01 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/02 13:42:33 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define	NUM_THREAD	8 // 변경 가능!

typedef struct	s_var
{
	int			max;
	int			sum;
	int			i;
}				t_var;

void	ft_multi_thread(int max);
void	*ft_sum(void *var);

int	main(void)
{
	int			max;

	max = 10000;
	ft_multi_thread(max);
	return (0);
}

void	ft_multi_thread(int max)
{
	pthread_t	threads[NUM_THREAD];
	t_var		var[NUM_THREAD];
	int			i;
	int			sum_all;

	i = 0;
	while (i < NUM_THREAD)
	{
		var[i].max = max;
		var[i].i = i;
		var[i].sum = 0;
		i++;
	}
	i = 0;
	while (i < NUM_THREAD)
	{
		pthread_create(&threads[i], NULL, ft_sum, &var[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREAD)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	sum_all = 0;
	i = 0;
	while (i < NUM_THREAD)
	{
		sum_all += var[i].sum;
		i++;
	}
	printf("sum: %d\n", sum_all);
}

void	*ft_sum(void *void_var)
{
	t_var	*var;
	int		i;

	var = (t_var *)void_var;
	i = var->i;
	while (i <= var->max)
	{
		usleep(300);
		var->sum += i;
		i += NUM_THREAD;
	}
	// printf("%d: %d\n", i, var->sum);
	return (NULL);
}
