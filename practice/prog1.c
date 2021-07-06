/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 01:50:19 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/02 01:55:40 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	max;
	int	sum;
	int	i;

	max = 10000;
	sum = 0;
	i = 1;
	while (i <= max)
	{
		usleep(200);
		sum += i;
		i++;
	}
	printf("sum: %d\n", sum);
	return (0);
}
