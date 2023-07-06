/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 10:54:25 by phunguye          #+#    #+#             */
/*   Updated: 2022/03/20 10:56:13 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
//Compares the first num bytes of the block of memory pointed by ptr1 
//to the first num bytes pointed by ptr2, returning zero if they all
//match or a value different from zero representing which is greater 
//if they do not.
//why does (unsigned char)s1[i] not work?
//must be (unsigned char *)&s[i] or ((unsigned char *)s1)[i]
/*#include <stdio.h>
#include <string.h>
int main () {
   char str1[15];
   char str2[15];
   int ret;

   memcpy(str1, "abcdef", 6);
   memcpy(str2, "aaCDEF", 6);

   ret = ft_memcmp(str1, str2, 5);

   if(ret > 0) {
      printf("str2 is less than str1 %d", ret);
   } else if(ret < 0) {
      printf("str1 is less than str2");
   } else {
      printf("str1 is equal to str2");
   }
   return(0);
}*/
