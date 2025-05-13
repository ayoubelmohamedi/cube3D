/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:09:35 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/13 15:26:06 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_texture_paths(t_env *env, t_cub *cub)
{
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
	player->cub = cub;
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

void	destroy_all_render(t_player *player)
{
	if (!player || !player->env)
		return ;
	if (player->env->img)
		mlx_destroy_image(player->env->mlx, player->env->img);
	if (player->env->has_wall_texture && player->env->walls)
	{
		if (player->env->walls->north_img)
			mlx_destroy_image(player->env->mlx, player->env->walls->north_img);
		if (player->env->walls->south_img)
			mlx_destroy_image(player->env->mlx, player->env->walls->south_img);
		if (player->env->walls->west_img)
			mlx_destroy_image(player->env->mlx, player->env->walls->west_img);
		if (player->env->walls->east_img)
			mlx_destroy_image(player->env->mlx, player->env->walls->east_img);
		free(player->env->walls);
	}
	if (player->env->win)
		mlx_destroy_window(player->env->mlx, player->env->win);
	mlx_destroy_display(player->env->mlx);
	free(player->env->mlx);
	destroy_data(player->cub->data, player->cub->texture);
	free(player->cub);
	free(player->env);
	free(player);
}

int	main(int ac, char **av)
{
	t_env			*env;
	t_player		*player;
	t_data			data;
	t_cub			*cub;
	t_wall_textures	*texture;

	if (ac != 2 || HEIGHT <= 0 || WIDTH <= 0)
		return (perror("Error: Invalid arguments\n"), 1);
	cub = malloc(sizeof(t_cub));
	texture = malloc(sizeof(t_wall_textures));
	if (!texture || !cub)
		return (free(cub), 1);
	ft_memset(cub, 0, sizeof(t_cub));
	ft_memset(&data, 0, sizeof(t_data));
	if (proccess_input(&data, cub, av[1], texture))
		return (free_heap(cub), 1);
	env = load_env(cub);
	player = init_player(env, cub);
	if (!env || !player)
		return (perror("Error: failed to initialize env or player"), 1);
	render_scene(env, player);
	mlx_hook(env->win, 2, 1L << 0, handle_keypress, player);
	mlx_loop(env->mlx);
	destroy_all_render(player);
	return (0);
}
