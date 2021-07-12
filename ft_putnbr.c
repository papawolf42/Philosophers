/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 23:28:30 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/09 00:28:09 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	ft_putnbr(long n)
{
	int			digit;
	static long	base[20] = {
		1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000,
		1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000,
		100000000000000, 1000000000000000, 10000000000000000,
		100000000000000000, 1000000000000000000
	};

	digit = ft_count_digit(n);
	ft_recursive_putnbr_fd(n, digit - 1, base, 9);
}

int	ft_count_digit(long nbr)
{
	int			digit;
	long		base;

	digit = 0;
	base = 1;
	if (nbr == 0)
		return (1);
	while (nbr >= base)
	{
		base *= 10;
		digit++;
	}
	return (digit);
}

void	ft_recursive_putnbr_fd(long n, int digit, long *base, int i)
{
	while (n < base[digit] * i && i > 0)
		i--;
	write(STDOUT, &DECIMAL[i], 1);
	if (digit > 0)
		ft_recursive_putnbr_fd(n - (base[digit] * i), digit - 1, base, 9);
}

void	ft_putnbr_ms(long n)
{
	int			digit;
	static long	base[20] = {
		1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000,
		1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000,
		100000000000000, 1000000000000000, 10000000000000000,
		100000000000000000, 1000000000000000000
	};
	static int	save[20] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	digit = ft_count_digit(n);
	ft_recursive_putnbr_fd_ms(n, digit - 1, base, save);
}

void	ft_recursive_putnbr_fd_ms(long n, int digit, long *base, int *save)
{
	int	i;

	i = 10;
	while (!(n < base[digit] * (save[digit] + 1) 
		&& n >= base[digit] * (save[digit])) && --i)
	{
		save[digit]++;
		if (save[digit] == 10)
			save[digit] = 0;
	}
	if (i == 0)
	{
		write(1, "0", 1);
		ft_recursive_putnbr_fd_ms(n, digit - 1, base, save);
		return ;
	}
	write(STDOUT, &DECIMAL[save[digit]], 1);
	if (digit > 0)
		ft_recursive_putnbr_fd_ms(n - (base[digit] * save[digit]), digit - 1,
			base, save);
}
