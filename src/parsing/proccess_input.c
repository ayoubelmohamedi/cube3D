/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:14:48 by aez-zoui          #+#    #+#             */
/*   Updated: 2025/05/07 14:09:13 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_extension(char *exten, char *s)
{
	int		len;
	char	*copy;
	int		i;
	bool	result;

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
		return (ft_freemap(&head), 1);
	if (convert_map(data, head))
		return (ft_freemap(&head), 1);
	close(fd);
	return (ft_freemap(&head), 0);
}


void fill_player_pos_dir(t_cub *cub)
{
    int i = 0;
    int j;
    char cell;
    bool found = false;

    while (i < cub->data->row)
    {
        j = 0;
        while (j < cub->data->col)
        {
            cell = cub->data->map[i][j];
            if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
            {
                cub->player_x = j + 0.5; 
                cub->player_y = i + 0.5;
                
                if (cell == 'N')
                    cub->p_angle = 3 * MM_PI / 2;  // Looking up
                else if (cell == 'S')
                    cub->p_angle = MM_PI / 2;      // Looking down
                else if (cell == 'E')
                    cub->p_angle = 0;             // Looking right
                else if (cell == 'W')
                    cub->p_angle = MM_PI;          // Looking left
                cub->data->map[i][j] = '0';
                found = true;
                break;
            }
            j++;
        }
        if (found)
            break;
        i++;
    }
    cub->data->i = i;
    cub->data->j = j;
    if (!found)
        printf("Error: No player position found in map\n");
}

int	start_parser(t_cub *cub, t_data *data, char *path, int fd)
{
	if (!check_extension(path, "cub"))
	{
		printf("Error in Extension\n");
		return (1);
	}
	if (valid_texture(cub, cub->texture, fd))
		return (1);
	if (check_map(data, path))
	{
		printf("Invalid Map\n");
		return (1);
	}
	fill_player_pos_dir(cub);
	return (0);
}

int	proccess_input(t_data *data, t_cub *cub, char *path, t_wall_textures *texture)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error in The file");
		(free(cub), free(texture));
		exit(1);
	}
	if (init_data(data))
		return (close(fd), 1);
	if (init_texture(texture))
		return (close(fd), 1);
	if (init_cub(cub, data, texture))
		return (close(fd), 1);
	if (start_parser(cub, data, path, fd))
	{
		destroy_data(cub->data, cub->texture);
		(free(cub), close(fd));
		exit(1);
	}
	close(fd);
	return (0);
}
