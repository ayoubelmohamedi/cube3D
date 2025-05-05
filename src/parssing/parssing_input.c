/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:29:57 by aez-zoui          #+#    #+#             */
/*   Updated: 2025/05/05 23:08:21 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_extension(char *exten, char *s)
{
	int		len;
	char	*copy;
	int		i;
	int		result;

	i = 0;
	len = ft_strlen(exten);
	copy = malloc(sizeof(char) * (len + 1));
	while (exten[len] != '.' && len > 0)
		len--;
	if (exten[len] == '.')
	{
		len++;
		while (exten[len] != '\0')
		{
			copy[i++] = exten[len++];
		}
	}
	copy[i] = '\0';
	result = ft_strncmp(s, copy, ft_strlen(s)) == 0;
	free(copy);
	return (result);
}

int	check_map(t_data *data, char *path)
{
	int			fd;
	t_maplist	*maplist;
	t_maplist	*head;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	maplist = get_map(fd);
	if (!maplist)
		return (1);
	head = maplist;
	if (validate_map(head))
		return (ft_mapclear(&head), 1);
	if (convert_map(data, head))
		return (ft_mapclear(&head), 1);
	close(fd);
	return (ft_mapclear(&head), 0);
}

void ft_printmap(char **map)
{
	int i = 0;
	int j ;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	start_parser(t_cub3d *cub, t_data *data, char *path, int fd)
{
	(void)cub;
	(void)fd;
	if (!check_extension(path, "cub"))
	{
		printf("Error in the extension \n");
		return (1);
	}
	if (valid_texture(cub, cub->my_textures, fd))
	 	return (1);
	if (check_map(data, path))
	{
		printf("Error in the map valeus \n");
		return (1);
	}
	//ft_printmap(cub->my_data->map);
	return (0);
}

int	parrsing_input(t_cub3d *cub, t_data *data, t_textures *texture, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error in The file map \n");
		(free(cub), free(texture));
		exit(1);
	}
	if (init_data(data))
		return (close(fd), 1);
	if (init_texture(texture))
		return (close(fd), 1);
	if (init_cub(cub, data, texture))
		return (close(fd), 1);
	if (start_parser(cub, data, file, fd))
	{
		(free(cub), close(fd));
		exit(1);
	}
	close(fd);
	return (0);
}
