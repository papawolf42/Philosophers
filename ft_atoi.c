/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 15:00:12 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/02 15:00:52 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_atoi(const char *nptr)
{
	unsigned long long	result;
	int					sign;

	result = 0;
	sign = 1;
	while ((9 <= *nptr && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign *= -1;
	while ('0' <= *nptr && *nptr <= '9')
	{
		result = result * 10 + *nptr - '0';
		nptr++;
	}
	if (result >= (unsigned long long)LONG_MAX && sign == 1)
		return (-1);
	else if (result >= (unsigned long long)LONG_MIN && sign == -1)
		return (0);
	return (sign * result);
}
