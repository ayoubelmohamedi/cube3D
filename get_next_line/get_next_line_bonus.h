/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bunus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:49:10 by aez-zoui          #+#    #+#             */
/*   Updated: 2023/12/06 21:14:00 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*ft_substr(char	*str, int start, int len);
char	*ft_strjoin(char *string, char	*buffer);
void	ft_joinstring(char *string, char *s1, char *s2);
size_t	ft_strlen(char	*str);
char	*get_next_line(int fd);
char	*ft_strdup(char *src);

#endif
