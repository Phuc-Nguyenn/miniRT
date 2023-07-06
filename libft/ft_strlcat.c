/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 10:57:57 by phunguye          #+#    #+#             */
/*   Updated: 2022/03/20 10:58:53 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	i = ft_strlen(dst);
	j = 0;
	while (src[j] != 0 && i + 1 < dstsize)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = 0;
	return (ft_strlen(dst) + ft_strlen(&src[j]));
}
//concatenate strings
/*
#include <stdio.h>
#include <string.h>

int main()
{
    char first[] = "This is ";
    char last[] = "a potentially long string";
    int r;
    int size = 16;
    char buffer[size];

    strcpy(buffer,first);
    r = strlcat(buffer,last,size);

    puts(buffer);
    printf("Value returned: %d\n",r);
    if( r > size )
        puts("String truncated");
    else
        puts("String was fully copied");

    return(0);
}
*/