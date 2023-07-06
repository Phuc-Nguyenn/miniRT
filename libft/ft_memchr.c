/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 10:54:13 by phunguye          #+#    #+#             */
/*   Updated: 2022/03/20 10:56:13 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)str)[i] == (unsigned char)c)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}
//searches for the first occurrence of the character c (an unsigned char) 
//in the first n bytes of the string pointed to, by the argument str.
/*
#include <stdio.h>
#include <string.h>
int main () {
   const char str[] = "http://www.tutorialspoint.com";
   const char ch = 't';
   char *ret;

   ret = memchr(str, ch, strlen(str));

   printf("String after |%c| is - |%s|\n", ch, ret);

   return(0);
}
*/