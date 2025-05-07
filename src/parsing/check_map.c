/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:11:42 by aez-zoui          #+#    #+#             */
/*   Updated: 2025/05/07 10:11:44 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_maplist	*check_lines(int fd, t_maplist **map)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
		{
			ft_freemap(map);
			free(line);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (*map);
}

int	checkline(char **line, int fd, t_maplist **map, int *start)
{
	if ((*line)[0] == '\n' && *start)
		return (check_lines(fd, map) == NULL);
	if (!skip_textures(line, fd))
		return (free(*line), 1);
	if (find_map(*line))
	{
		if (is_valid_characters(*line))
		{
			ft_freemap(map);
			return (free(*line), 1);
		}
		add_map_node(map, *line);
		*start = 1;
	}
	return (0);
}

void	process_line(t_data *data, t_maplist *temp)
{
	while (temp->line[data->j])
	{
		if (temp->line[data->j] == ' ' || temp->line[data->j] == '\t'
			|| temp->line[data->j] == '\n')
			data->map[data->i][data->j] = '1';
		else
			data->map[data->i][data->j] = temp->line[data->j];
		data->j++;
	}
	while (data->j < data->col)
		data->map[data->i][data->j++] = '1';
	data->map[data->i][data->j] = '\0';
	data->i++;
}

int	init_map(t_maplist *m, t_data *data)
{
	t_maplist	*temp;

	data->col = get_biggest_line(m);
	temp = m;
	while (temp)
	{
		data->row++;
		temp = temp->next;
	}
	data->map = malloc(sizeof(char *) * (data->row + 1));
	if (!data->map)
		return (1);
	return (0);
}

int	convert_map(t_data *data, t_maplist *m)
{
	t_maplist	*temp;

	if (init_map(m, data))
		return (1);
	temp = m;
	while (data->i < data->row)
	{
		data->map[data->i] = malloc(data->col + 1);
		if (!data->map[data->i])
			return (free_array(data->map), 1);
		data->j = 0;
		process_line(data, temp);
		temp = temp->next;
	}
	data->map[data->row] = NULL;
	return (0);
}
