/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:38:50 by ayel-mou          #+#    #+#             */
/*   Updated: 2025/02/26 05:40:18 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_count_words(const char *s, char c)
{
	size_t	count;
	size_t	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

void	find_next_word(const char *s, size_t *start, char c, size_t *end)
{
	while (s[*start] && s[*start] == c)
		(*start)++;
	*end = *start;
	while (s[*end] && s[*end] != c)
		(*end)++;
}

char	*allocate_and_copy_word(const char *s, size_t start, size_t end)
{
	size_t	i;
	char	*word;

	i = 0;
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	while (i < end - start)
	{
		word[i] = s[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**allocate_words(char const *s, char c, char **array, size_t word_count)
{
	size_t	i;
	size_t	j;
	size_t	end;

	i = 0;
	j = 0;
	while (s[i] && j < word_count)
	{
		find_next_word(s, &i, c, &end);
		if (s[i])
		{
			array[j] = allocate_and_copy_word(s, i, end);
			if (!array[j])
			{
				while (j + 1)
					free(array[j--]);
				free(array);
				return (0);
			}
			j++;
			i = end;
		}
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	char	**array;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!array)
		return (NULL);
	return (allocate_words(s, c, array, word_count));
}
