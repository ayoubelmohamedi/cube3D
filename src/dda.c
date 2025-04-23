

#include "cub3d.h"


double dda_algo(double rayDirX, double rayDirY, double *rayX, double *rayY, int *mapX, int *mapY, int *side)
{

    int side_hit = 0;
    // Initialize mapX and mapY to the player's current grid position
    *mapX = (int)(*rayX);
    *mapY = (int)(*rayY);

    // Calculate delta distances
    double deltaDistX = fabs(1 / rayDirX);
    double deltaDistY = fabs(1 / rayDirY);

    // Determine step direction and initial side distances
    int stepX = (rayDirX < 0) ? -1 : 1;
    int stepY = (rayDirY < 0) ? -1 : 1;

    double sideDistX = (rayDirX < 0) ? (*rayX - *mapX) * deltaDistX : (*mapX + 1.0 - *rayX) * deltaDistX;
    double sideDistY = (rayDirY < 0) ? (*rayY - *mapY) * deltaDistY : (*mapY + 1.0 - *rayY) * deltaDistY;

    // Perform DDA
    while (1)
    {
        // Jump to the next grid cell
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            *mapX += stepX;
            side_hit = 0; // hit vertical line  (East or West)
        }
        else
        {
            sideDistY += deltaDistY;
            *mapY += stepY;
            side_hit = 1; // hit a horizontal wall (NORTH or SOUTH)
        }

        // check bound before check
        if (*mapX < 0 || *mapX >= MAP_WIDTH || *mapY < 0 || *mapY >= MAP_HEIGHT)
            return (-1.0);

        // Check if a wall is hit
        if (map[*mapY][*mapX] > 0)
            break;
    }
    // (wallX - playerX + (1 - stepX) / 2) / rayDirX
    if (side_hit == 0)
    {
        *side = (rayDirX > 0) ? SIDE_WEST : SIDE_EAST;
        return (sideDistX - deltaDistX);
    }
    else
    {
        *side = (rayDirY > 0) ? SIDE_NORTH : SIDE_SOUTH;
        return (sideDistY - deltaDistY);
    }
}

