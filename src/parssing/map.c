/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:27:22 by aez-zoui          #+#    #+#             */
/*   Updated: 2025/05/05 21:19:47 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_maplist	*create_map(char *line)
{
	t_maplist	*node;

	node = (t_maplist *)malloc(sizeof(t_maplist));
	if (!node)
		return (NULL);
	node->line = ft_strdup(line);
	node->next = NULL;
	return (node);
}

void	add_map_node(t_maplist **head, char *line)
{
	t_maplist	*node;
	t_maplist	*temp;

	node = create_map(line);
	if (!node)
		return ;
	if (*head == NULL)
		*head = node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}

t_maplist	*get_map(int fd)
{
	char		*line;
	t_maplist	*map;
	int			start;

	map = NULL;
	start = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (process_map(&line, fd, &map, &start))
			return (NULL);
		free(line);
		line = get_next_line(fd);
	}
	return (map);
}

int	is_valid_characters(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& line[i] != '\t' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	skip_textures(char **line, int fd)
{
	while (*line && (!ft_strncmp(*line, "NO ", 3) || !ft_strncmp(*line, "SO ",
				3) || !ft_strncmp(*line, "WE ", 3) || !ft_strncmp(*line, "EA ",
				3) || (*line)[0] == 'F' || (*line)[0] == 'C'))
	{
		free(*line);
		*line = get_next_line(fd);
	}
	return (*line != NULL);
}
