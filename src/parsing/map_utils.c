/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:14:04 by aez-zoui          #+#    #+#             */
/*   Updated: 2025/05/07 10:14:06 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*remove_spaces(char *str)
{
	char	*new_str;

	if (!str)
		return (NULL);
	while (*str && *str == ' ')
		str++;
	new_str = ft_strdup(str);
	if (!new_str)
		return (NULL);
	return (new_str);
}

int	is_invalid_texture(char *str)
{
	if (ft_strncmp(str, "NO", 2) && ft_strncmp(str, "SO", 2) && ft_strncmp(str,
			"WE", 2) && ft_strncmp(str, "EA", 2) && ft_strncmp(str, "F", 1)
		&& ft_strncmp(str, "C", 1))
		return (1);
	return (0);
}

int	get_biggest_line(t_maplist *head)
{
	int	big_line;
	int	current_len;

	big_line = 0;
	while (head)
	{
		current_len = ft_strlen(head->line);
		if (current_len > big_line)
			big_line = current_len;
		head = head->next;
	}
	return (big_line);
}

int	is_not_closed(t_maplist *prev, t_maplist *current, t_maplist *next)
{
	int	i;

	i = 0;
	while (current->line[i])
	{
		if (current->line[i] == '0' || current->line[i] == 'N'
			|| current->line[i] == 'S' || current->line[i] == 'W'
			|| current->line[i] == 'E')
		{
			if (check_space(current->line[i - 1]))
				return (1);
			if (check_space(current->line[i + 1]))
				return (1);
			if (!prev || i >= (int)ft_strlen(prev->line)
				|| check_space(prev->line[i]))
				return (1);
			if (!next || i >= (int)ft_strlen(next->line)
				|| check_space(next->line[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	validate_map(t_maplist *map)
{
	t_maplist	*prev;
	t_maplist	*next;
	t_maplist	*current;

	if (!map)
		return (1);
	prev = NULL;
	current = map;
	while (current)
	{
		next = current->next;
		if (is_not_closed(prev, current, next))
			return (1);
		prev = current;
		current = next;
	}
	return (0);
}
