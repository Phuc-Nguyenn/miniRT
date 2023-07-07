/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 10:54:03 by phunguye          #+#    #+#             */
/*   Updated: 2022/03/20 10:56:13 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	digitcount(int n)
{
	int	digits;

	digits = 0;
	if (n <= 0)
	{
		digits++;
		n *= -1;
	}
	while (n)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

int	maxint(char *numstr)
{
	numstr[0] = '-';
	numstr[1] = '2';
	return (147483648);
}

char	*ft_itoa(int n)
{
	char	*numstr;
	int		i;
	int		digits;

	digits = digitcount(n);
	numstr = (char *)malloc(digits + 1);
	if (!numstr)
		return (NULL);
	if (n == -2147483648)
		n = maxint(numstr);
	if (n < 0)
	{
		numstr[0] = '-';
		n *= -1;
	}
	i = digits - 1;
	if (n == 0)
		numstr[i] = '0';
	while (n)
	{
		numstr[i--] = '0' + (n % 10);
		n /= 10;
	}
	numstr[digits] = 0;
	return (numstr);
}

/*
#include <stdio.h>
int main()
{
	printf("%s\n", ft_itoa(-635));
	printf("%s\n", ft_itoa(-0));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(9785));
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(00454305));
	return(0);
}*/