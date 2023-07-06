/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:03:00 by phunguye          #+#    #+#             */
/*   Updated: 2022/12/09 22:37:23 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFFER_SIZE 30

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_new_save(char *save);
char	*ft_read_fd(int fd, char *save);
char	*ft_get_line(char *save);
char	*get_next_line(int fd);

#endif