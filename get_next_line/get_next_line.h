/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:16:52 by aez-zoui          #+#    #+#             */
/*   Updated: 2023/12/06 21:46:25 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*ft_strdup(char *str);
char	*ft_strjoin(char *str, char *buffer);
size_t	ft_strlen(char *str);
char	*ft_substr(char *string, int start, int len);
char	*get_next_line(int fd);
void	ft_joinstring(char *string, char *str, char *buffer);

#endif
