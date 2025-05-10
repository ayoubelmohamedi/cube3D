/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:48:49 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/10 20:49:32 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_north_texture(t_player *player, t_texture_info *tex)
{
    tex->addr = player->env->walls->north_addr;
    tex->width = player->env->walls->north_width;
    tex->height = player->env->walls->north_height;
    tex->bpp = player->env->walls->north_bpp;
    tex->line_len = player->env->walls->north_line_len;
}

void	set_south_texture(t_player *player, t_texture_info *tex)
{
    tex->addr = player->env->walls->south_addr;
    tex->width = player->env->walls->south_width;
    tex->height = player->env->walls->south_heght;
    tex->bpp = player->env->walls->south_bpp;
    tex->line_len = player->env->walls->south_line_len;
}

void	set_east_texture(t_player *player, t_texture_info *tex)
{
    tex->addr = player->env->walls->east_addr;
    tex->width = player->env->walls->east_width;
    tex->height = player->env->walls->east_height;
    tex->bpp = player->env->walls->east_bpp;
    tex->line_len = player->env->walls->east_line_len;
}

void	set_west_texture(t_player *player, t_texture_info *tex)
{
    tex->addr = player->env->walls->west_addr;
    tex->width = player->env->walls->west_width;
    tex->height = player->env->walls->west_height;
    tex->bpp = player->env->walls->west_bpp;
    tex->line_len = player->env->walls->west_line_len;
}