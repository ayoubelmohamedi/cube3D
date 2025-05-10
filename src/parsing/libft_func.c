/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:40:59 by aez-zoui          #+#    #+#             */
/*   Updated: 2025/05/09 16:41:04 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	len;

	len = 0;
	if (size != 0)
	{
		while (src[len] != '\0' && len < size - 1)
		{
			dst[len] = src[len];
			len++;
		}
		dst[len] = '\0';
	}
	return (ft_strlen(src));
}

int	check_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void	*ft_memset(void *ptr, int x, size_t n)
{
	unsigned char	*str;
	unsigned char	v;
	size_t			i;

	v = (unsigned char)x;
	str = ptr;
	i = 0;
	while (i < n)
	{
		str[i] = v;
		i++;
	}
	return (ptr);
}
