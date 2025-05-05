/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:16:55 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/05 21:38:35 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"

// Helper functions for key handling

static int	handle_exit(t_player *player)
{
    mlx_destroy_image(player->env->mlx, player->env->img);
    mlx_destroy_window(player->env->mlx, player->env->win);
    exit(0);
    return (0);
}

static int	handle_movement(int key, t_player *player)
{
    double	new_x;
    double	new_y;

    if (key == KEY_W)
    {
        new_x = player->x + cos(player->dir) * MOVE_SPEED;
        new_y = player->y + sin(player->dir) * MOVE_SPEED;
    }
    else if (key == KEY_S)
    {
        new_x = player->x - cos(player->dir) * MOVE_SPEED;
        new_y = player->y - sin(player->dir) * MOVE_SPEED;
    }
    else if (key == KEY_A)
    {
        new_x = player->x + sin(player->dir) * MOVE_SPEED;
        new_y = player->y - cos(player->dir) * MOVE_SPEED;
    }
    else
    {
        new_x = player->x - sin(player->dir) * MOVE_SPEED;
        new_y = player->y + cos(player->dir) * MOVE_SPEED;
    }
    if (player->env->map[(int)new_y][(int)new_x] == '0')
    {
        player->x = new_x;
        player->y = new_y;
        return (1);
    }
    return (0);
}

static int	handle_rotation(int key, t_player *player)
{
    if (key == KEY_LEFT)
    {
        player->dir -= ROTATE_SPEED;
        if (player->dir < 0)
            player->dir += 2 * M_PI;
    }
    else
    {
        player->dir += ROTATE_SPEED;
        if (player->dir >= 2 * M_PI)
            player->dir -= 2 * M_PI;
    }
    return (1);
}

int	handle_keypress(int keypress, t_player *player)
{
    bool	need_render;

    need_render = false;
    if (keypress == KEY_ESC)
        return (handle_exit(player));
    if (keypress == KEY_W || keypress == KEY_S || 
        keypress == KEY_A || keypress == KEY_D)
        need_render = handle_movement(keypress, player);
    if (keypress == KEY_LEFT || keypress == KEY_RIGHT)
        need_render = handle_rotation(keypress, player);
    if (need_render)
        render_scene(player->env, player);
    return (0);
}