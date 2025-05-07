/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:15:25 by aez-zoui          #+#    #+#             */
/*   Updated: 2025/05/07 10:15:28 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	set_texture_path(t_wall_textures *texture, char *line, char *trimmed)
{
	if (!ft_strncmp(line, "NO", 2))
	{
		if (texture->no)
			return (1);
		texture->no = ft_strdup(trimmed);
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		if (texture->so)
			return (1);
		texture->so = ft_strdup(trimmed);
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		if (texture->we)
			return (1);
		texture->we = ft_strdup(trimmed);
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		if (texture->ea)
			return (1);
		texture->ea = ft_strdup(trimmed);
	}
	return (0);
}

int	texture_path(t_wall_textures *texture, char *line, char *trimmed)
{
	if (is_invalid_texture(line))
		return (1);
	if (!ft_strncmp(line, "F", 1))
	{
		if (texture->rgb->f)
			return (1);
		texture->rgb->f = ft_strdup(trimmed);
		return (free(trimmed), 0);
	}
	else if (!ft_strncmp(line, "C", 1))
	{
		if (texture->rgb->c)
			return (1);
		texture->rgb->c = ft_strdup(trimmed);
		return (free(trimmed), 0);
	}
	else if (!set_texture_path(texture, line, trimmed))
		return (free(trimmed), 0);
	return (1);
}

int	parse_texture_line(t_wall_textures *texture, char *line)
{
	char	*trimmed;
	int		ret;
	char	*new_line;

	new_line = NULL;
	new_line = remove_spaces(line);
	if (new_line[0] == '1' || new_line[0] == '0')
		return (free(new_line), free(line), 0);
	free(line);
	trimmed = ft_strtrim(&new_line[2], " \t\n");
	if (!trimmed)
		return (free(new_line), 1);
	ret = texture_path(texture, new_line, trimmed);
	free(new_line);
	if (ret == 0)
		return (0);
	if (ret == 1)
		return (free(trimmed), 1);
	return (1);
}

int	read_texture_lines(t_wall_textures *texture, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (line[0] == '1' || line[0] == '0')
		{
			free(line);
			break ;
		}
		if (parse_texture_line(texture, line))
			return (1);
		line = get_next_line(fd);
	}
	return (0);
}

int	valid_texture(t_cub *cub, t_wall_textures *texture, int fd)
{
	(void)cub;
	if (read_texture_lines(texture, fd))
	{
		printf("Error in The TEXTURES");
		return (1);
	}
	else if (!texture->no || !texture->so || !texture->we || !texture->ea
		|| !texture->rgb->f || !texture->rgb->c)
	{
		printf("Error in The TEXTURES");
		return (1);
	}
	else if (parse_texture_extension(texture))
	{
		printf("Error in the extension\n");
		return (1);
	}
	else if (check_colors(texture))
	{
		printf("Error in The Colors\n");
		return (1);
	}
	else
		return (0);
}
