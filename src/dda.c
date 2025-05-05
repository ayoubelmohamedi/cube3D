/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:04:49 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/05 21:32:02 by ael-moha         ###   ########.fr       */
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

static void	init_dda(double rayDirX, double rayDirY, double *rayX,
                    double *rayY, int *mapX, int *mapY, t_dda *dda)
{
    *mapX = (int)(*rayX);
    *mapY = (int)(*rayY);
    dda->deltaDistX = fabs(1 / rayDirX);
    dda->deltaDistY = fabs(1 / rayDirY);
    dda->stepX = (rayDirX < 0) ? -1 : 1;
    dda->stepY = (rayDirY < 0) ? -1 : 1;
    dda->sideDistX = (rayDirX < 0) ? (*rayX - *mapX) * dda->deltaDistX
        : (*mapX + 1.0 - *rayX) * dda->deltaDistX;
    dda->sideDistY = (rayDirY < 0) ? (*rayY - *mapY) * dda->deltaDistY
        : (*mapY + 1.0 - *rayY) * dda->deltaDistY;
    dda->side_hit = 0;
}

static int	perform_dda(int *mapX, int *mapY, t_dda *dda)
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
    if (map[*mapY][*mapX] > 0)
        return (1);
    return (0);
}

double	dda_algo(double rayDirX, double rayDirY, double *rayX,
                double *rayY, int *mapX, int *mapY, int *side)
{
    t_dda	dda;
    int		result;

    init_dda(rayDirX, rayDirY, rayX, rayY, mapX, mapY, &dda);
    while (1)
    {
        result = perform_dda(mapX, mapY, &dda);
        if (result == -1)
            return (-1.0);
        if (result == 1)
            break ;
    }
    if (dda.side_hit == 0)
    {
        *side = (rayDirX > 0) ? SIDE_WEST : SIDE_EAST;
        return (dda.sideDistX - dda.deltaDistX);
    }
    else
    {
        *side = (rayDirY > 0) ? SIDE_NORTH : SIDE_SOUTH;
        return (dda.sideDistY - dda.deltaDistY);
    }
}

