/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superlib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:24:43 by ayel-mou          #+#    #+#             */
/*   Updated: 2025/02/26 05:38:44 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
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

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;
	size_t	j;
	int		found;

	i = 0;
	while (s[i])
	{
		j = 0;
		found = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
			{
				found = 1;
				break ;
			}
			j++;
		}
		if (!found)
			return (i);
		i++;
	}
	return (i);
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
