/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:04:49 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/09 11:35:58y ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"

typedef struct s_dda
{
    int		side_hit;
    int		stepX;
    int		stepY;
    double	deltaDistX;
    double	deltaDistY;
    double	sideDistX;
    double	sideDistY;
}	t_dda;


static void	init_dda(t_rays *rays, t_dda *dda)
{
    rays->mapX = (int)*rays->rayX;
    rays->mapY = (int)*rays->rayY;
    dda->deltaDistX = fabs(1 / rays->rayDirX);
    dda->deltaDistY = fabs(1 / rays->rayDirY);
    dda->stepX = (rays->rayDirX < 0) ? -1 : 1;
    dda->stepY = (rays->rayDirY < 0) ? -1 : 1;
    dda->sideDistX = (rays->rayDirX < 0) ? (*rays->rayX - rays->mapX) * dda->deltaDistX
        : (rays->mapX + 1.0 - *rays->rayX) * dda->deltaDistX;
    dda->sideDistY = (rays->rayDirY < 0) ? (*rays->rayY - rays->mapY) * dda->deltaDistY
        : (rays->mapY + 1.0 - *rays->rayY) * dda->deltaDistY;
    dda->side_hit = 0;
}

static int	perform_dda(int *mapX, int *mapY, t_dda *dda, t_player *player)
{
    if (dda->sideDistX < dda->sideDistY)
    {
        dda->sideDistX += dda->deltaDistX;
        *mapX += dda->stepX;
        dda->side_hit = 0;
    }
    else
    {
        dda->sideDistY += dda->deltaDistY;
        *mapY += dda->stepY;
        dda->side_hit = 1;
    }
    if (*mapX < 0 || *mapX >= player->env->map_width || *mapY < 0 || *mapY >= player->env->map_height)
        return (-1);
    if ((player->env->map[*mapY][*mapX]) != '0')
        return (1);
    return (0);
}

double	dda_algo(t_rays *rays,int *side, t_player *player)
{
    t_dda	dda;
    int		result;

    init_dda(rays, &dda);
    while (1)
    {
        result = perform_dda(&rays->mapX, &rays->mapY, &dda, player);
        if (result == -1)
            return (-1.0);
        if (result == 1)
            break ;
    }
    if (dda.side_hit == 0)
    {
        *side = (rays->rayDirX > 0) ? SIDE_WEST : SIDE_EAST;
        return (dda.sideDistX - dda.deltaDistX);
    }
    else
    {
        *side = (rays->rayDirY > 0) ? SIDE_NORTH : SIDE_SOUTH;
        return (dda.sideDistY - dda.deltaDistY);
    }
}

