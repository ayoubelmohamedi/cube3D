#include "includes/cub3d.h"

int	ft_exit(t_cub *cub)
{
	destroy_all(cub);
	exit(0);
	return (0);
}

void ft_print_map(char **map)
{
	int i , j;
	i = 0;
	j = 0;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			printf("%c",map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}


int	main(int ac, char **av)
{
	t_data		data;
	t_cub		*cub;
	t_texture	*texture;

	if (ac != 2)
		printf("Error ARG\n");
	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (1);
	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (free(cub), 1);
	ft_memset(cub, 0, sizeof(t_cub));
	ft_memset(&data, 0, sizeof(t_data));
	if (proccess_input(&data, cub, av[1], texture))
			return (free_heap(cub), 1);
	
	printf("\n=================== MAP =====================\n\n");
	ft_print_map(cub->data->map);

	printf("\n=================== TEXTURES ================\n\n");
	printf("NO :%s \n", cub->texture->no);
	printf("EA :%s \n", cub->texture->ea);
	printf("WE :%s \n", cub->texture->we);
	printf("SO :%s \n", cub->texture->so);

	return (0);
}
