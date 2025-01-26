
#include "cub3d.h"

// int ft_strlen(char *str)
// {
// 	int i = 0;
// 	while (str && str[i])
// 		i++;
// 	return (i);
// }

void	ft_msg_exit(char *msg)
{
	int i;

	i = 0;
	while (msg && msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
	exit(2);
}

void check_extension(char *file)
{
	int len;

	len = ft_strlen(file);
	if (file[len - 1] != 'b' || file[len - 2] != 'u' || file[len - 3] != 'c'
			|| file[len - 4] != '.')
		ft_msg_exit("Error Extension\n");
}

void ft_printdata(char **substr)
{
	int i = 0;
	while (substr[i])
	{
		printf("%s",substr[i]);
		break;
	}
	printf("\n=============\n");
}

int get_type_data(const char *prefix)
{
	if (!strcmp(prefix, " "))
		return (0);
	else if(!strcmp(prefix, "F"))
		return (1);
	else if (!strcmp(prefix, "C"))
		return (2);
	else if (!strcmp(prefix, "NO"))
		return (3);
	else if (!strcmp(prefix, "SO"))
		return (4);
	else if (!strcmp(prefix, "WE"))
		return (5);
	else if (!strcmp(prefix, "EA"))
		return (6);
	else
		return (-1);
}

void check_error_rgb(char **rgb)
{
	int i;
	i = 0;

	while(rgb[i])
		i++;
	if (i != 3)
		exit(-1);
}


void check_rgb(char *rgb)
{
	int i;
	int err = 0;

	i = 0;
	if(!rgb)
		exit (-1);
	while(rgb[i])
	{
		if (rgb[i] == ',')
			err++;
		i++;
	}
	if (err != 2)
		exit(-1);
	
	// Some free here
}

t_rgb *save_rgb(char *data)
{
	t_rgb *rgb;
	char **r_g_b;

	check_rgb(data);
	rgb = (t_rgb *)malloc(sizeof(t_rgb));
    if (!rgb)
		return NULL;
	r_g_b = ft_split(data,',');
	rgb->r = atoi(r_g_b[0]);
	rgb->g = atoi(r_g_b[1]);
	rgb->b = atoi(r_g_b[2]);

	// do free split
	return (rgb);
}

int save_elemt(int type, char *data, t_textures_data *elemts_data)
{
	if (type == 1)
		elemts_data->floor_color = save_rgb(data);
	else if (type == 2)
		elemts_data->ceil_color = save_rgb(data);
	else if (type == 3)
		elemts_data->no_texture = ft_strdup(data);
	else if (type == 4)
		elemts_data->so_texture = ft_strdup(data);
	else if (type == 5)
		elemts_data->we_texture = ft_strdup(data);
	else if (type == 6)
		elemts_data->ea_texture = ft_strdup(data);
	else
		return (0);
}

void ft_printf_data_maps(t_textures_data *map)
{
	printf("R = %d\n",map->ceil_color->r);
	printf("G = %d\n",map->ceil_color->g);
	printf("B = %d\n",map->ceil_color->b);
	printf("R = %d\n",map->floor_color->r);
	printf("G = %d\n",map->floor_color->g);
	printf("B = %d\n",map->floor_color->b);
	printf("=================================\n");
	printf("-->%s\n",map->ea_texture);
	printf("-->%s\n",map->so_texture);
	printf("-->%s\n",map->we_texture);
	printf("-->%s\n",map->ea_texture);

}


void save_map(t_textures_data *ma)
{
	int i;
	int j;

	i = 0;
	while (i < get_line(ma))
	{
		while (j < get_line(ma))
	}

}

void save_check_elements(int fd, t_textures_data *elem_dt)
{
	char *line;
	int len_elmet;
	char **subline;

	len_elmet = 0;
	line = get_next_line(fd);
	while (line)
	{
		subline = ft_split(line, ' ');
		if(len_elmet == 6 && subline[0][0] == '1')
		{
			free_split(subline);
			break;
		}
		if (subline[0] == NULL || subline[0][0] == '\n' || subline[0][0] == '\n')
		{
			//free(line);
			//free_split(subline);
			line = get_next_line(fd);
			continue;
		}
		line = get_next_line(fd);
		int  type = get_type_data(subline[0]);
		/*
		| save_elemt()
	    |
		| F 0,135,206
		| C 99,99,99
		| NO textures/7it2.xpm
        | SO textures/7itlkhr.xpm
        | WE textures/7itakhor.xpm
        | EA textures/7it3.xpm
		*/
		save_elemt(type, subline[1], elem_dt);
		//free_split(subline);
		//free(line);
	}
	ft_printf_data_maps(elem_dt);
	/*
	* save_map()
	*
	* 111111111111111
	* 100000000000001
	* 100000000000001
	* 111111111111111
	*/
	save_map(elem_dt);
}

void	check_file_map(char *file,t_textures_data *elementes_data)
{
	int fd;
	check_extension(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_msg_exit("Error in Open file\n");
	save_check_elements(fd, elementes_data);

	close(fd);
}
