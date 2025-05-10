/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:15:42 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/05 22:05:36by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


t_wall_text	*load_walls_texture(t_env *env)
{
    t_wall_text	*walls_tex;

    walls_tex = (t_wall_text *)malloc(sizeof(t_wall_text));
    if (!walls_tex)
        return (NULL);
    if (load_north_texture(env, walls_tex))
        return (free(walls_tex), NULL);
    if (load_south_texture(env, walls_tex))
        return (free(walls_tex), NULL);
    if (load_west_texture(env, walls_tex))
        return (free(walls_tex), NULL);
    if (load_east_texture(env, walls_tex))
        return (free(walls_tex), NULL);
    return (walls_tex);
}

void	init_texture_paths(t_env *env, t_cub *cub)
{
	// textures paths for [no, so, we,ea]
	env->wall_tex_files[0] = cub->texture->no;
	env->wall_tex_files[1] = cub->texture->so;
	env->wall_tex_files[2] = cub->texture->we;
	env->wall_tex_files[3] = cub->texture->ea;
    env->has_wall_texture = true;
	env->f_color = get_colors(cub->texture->rgb->f);
	env->c_color = get_colors(cub->texture->rgb->c);
}

t_player	*init_player(t_env *env, t_cub *cub)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->env = env;
	player->x = cub->player_x;
	player->y = cub->player_y;
	player->dir = cub->p_angle;
	return (player);
}

t_env	*load_env(t_cub *cub)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->map = cub->data->map;
	env->map_width = cub->data->col;
	env->map_height = cub->data->row;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Raycasting Demo");
	env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel,
			&env->line_lenght, &env->endian);
	init_texture_paths(env, cub);
	if (env->has_wall_texture)
		env->walls = load_walls_texture(env);
	return (env);
}

int	main(int ac, char **av)
{
	t_env			*env;
	t_player		*player;
	t_data			data;
	t_cub			*cub;
	t_wall_textures	*texture;

	if (ac != 2)
	{
		printf("Error ARG\n");
		return (1);
	}
	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (1);
	texture = malloc(sizeof(t_wall_textures));
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
	// destroy_all(cub);
	env = load_env(cub);
	player = init_player(env, cub);
	// test env and player
	if (!env || !player)
	{
		perror("Error: failed to initialize env or player");
		return (1);
	}
	// display content of env and player
	printf("env->map_width: %d\n", env->map_width);
	printf("env->map_height: %d\n", env->map_height);
	// print all player attributes
	printf("player->x: %f\n", player->x);
	printf("player->y: %f\n", player->y);
	printf("player->dir: %f\n", player->dir);
	printf("env->f_color: %d\n", env->f_color);
	printf("env->c_color: %d\n", env->c_color);
	printf("env->has_texture: %d\n", env->has_texture);
	printf("env->has_wall_texture: %d\n", env->has_wall_texture);
	printf("env->has_minimap: %d\n", env->has_minimap);
	render_scene(env, player);
	mlx_hook(env->win, 2, 1L << 0, handle_keypress, player);
	mlx_loop(env->mlx);
	return (0);
}
