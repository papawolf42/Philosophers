/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_of_day.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 02:11:56 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/04 23:50:41 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

int	main(void)
{
	struct timeval	timeval;
	long	ms;

	gettimeofday(&timeval, NULL);
	ms = timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	printf("timeofday: %ld in ms\n", ms);
}
