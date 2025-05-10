/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_helpers2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 22:46:55 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/10 22:47:21 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_north_texture(t_env *env, t_wall_text *walls_tex)
{
	walls_tex->north_img = mlx_xpm_file_to_image(env->mlx,
			env->wall_tex_files[0], &walls_tex->north_width,
			&walls_tex->north_height);
	if (!walls_tex->north_img)
		return (1);
	walls_tex->north_addr = mlx_get_data_addr(walls_tex->north_img,
			&walls_tex->north_bpp, &walls_tex->north_line_len,
			&walls_tex->north_endian);
	return (0);
}

int	load_south_texture(t_env *env, t_wall_text *walls_tex)
{
	walls_tex->south_img = mlx_xpm_file_to_image(env->mlx,
			env->wall_tex_files[1], &walls_tex->south_width,
			&walls_tex->south_heght);
	if (!walls_tex->south_img)
		return (1);
	walls_tex->south_addr = mlx_get_data_addr(walls_tex->south_img,
			&walls_tex->south_bpp, &walls_tex->south_line_len,
			&walls_tex->south_endian);
	return (0);
}

int	load_west_texture(t_env *env, t_wall_text *walls_tex)
{
	walls_tex->west_img = mlx_xpm_file_to_image(env->mlx,
			env->wall_tex_files[2], &walls_tex->west_width,
			&walls_tex->west_height);
	if (!walls_tex->west_img)
		return (1);
	walls_tex->west_addr = mlx_get_data_addr(walls_tex->west_img,
			&walls_tex->west_bpp, &walls_tex->west_line_len,
			&walls_tex->west_endian);
	return (0);
}

int	load_east_texture(t_env *env, t_wall_text *walls_tex)
{
	walls_tex->east_img = mlx_xpm_file_to_image(env->mlx,
			env->wall_tex_files[3], &walls_tex->east_width,
			&walls_tex->east_height);
	if (!walls_tex->east_img)
		return (1);
	walls_tex->east_addr = mlx_get_data_addr(walls_tex->east_img,
			&walls_tex->east_bpp, &walls_tex->east_line_len,
			&walls_tex->east_endian);
	return (0);
}
