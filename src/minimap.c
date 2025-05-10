

#include "../includes/cub3d.h"

void	render_minimap(t_env *env, t_player *player)
{
	int	mapX;
	int	mapY;
	int	color;
	int	dest_color;
	int	r;
	int	g;
	int	b;
	int	playerScreenX;
	int	playerScreenY;
	int	dirX;
	int	dirY;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	for (int y = 0; y < MINIMAP_SIZE; y++)
	{
		for (int x = 0; x < MINIMAP_SIZE; x++)
		{
			if (x < 2 || y < 2 || x >= MINIMAP_SIZE - 2 || y >= MINIMAP_SIZE
				- 2)
			{
				my_mlx_pixel_put(env, MINIMAP_X + x, MINIMAP_Y + y,
					MINIMAP_BORDER_COLOR);
				continue ;
			}
			mapX = (int)((x - MINIMAP_SIZE / 2) / MINIMAP_SCALE + player->x);
			mapY = (int)((y - MINIMAP_SIZE / 2) / MINIMAP_SCALE + player->y);
			if (mapX >= 0 && mapX < player->env->map_width && mapY >= 0
				&& mapY < player->env->map_height)
			{
				color = (player->env->map[mapY][mapX] != '0') ? MINIMAP_WALL_COLOR : MINIMAP_FLOOR_COLOR;
				dest_color = 0x000000;
				r = (int)(MINIMAP_OPACITY * ((color >> 16) & 0xFF) + (1
							- MINIMAP_OPACITY) * ((dest_color >> 16) & 0xFF));
				g = (int)(MINIMAP_OPACITY * ((color >> 8) & 0xFF) + (1
							- MINIMAP_OPACITY) * ((dest_color >> 8) & 0xFF));
				b = (int)(MINIMAP_OPACITY * (color & 0xFF) + (1
							- MINIMAP_OPACITY) * (dest_color & 0xFF));
				my_mlx_pixel_put(env, MINIMAP_X + x, MINIMAP_Y + y,
					(r << 16) | (g << 8) | b);
			}
			else
			{
				my_mlx_pixel_put(env, MINIMAP_X + x, MINIMAP_Y + y, DARK_COLOR);
			}
		}
	}
	playerScreenX = MINIMAP_X + MINIMAP_SIZE / 2;
	playerScreenY = MINIMAP_Y + MINIMAP_SIZE / 2;
	dirX = playerScreenX + cos(player->dir) * PLAYER_DIR_LENGTH;
	dirY = playerScreenY + sin(player->dir) * PLAYER_DIR_LENGTH;
	// Simple line drawing algorithm (Bresenham)
	dx = abs(dirX - playerScreenX);
	dy = abs(dirY - playerScreenY);
	sx = (playerScreenX < dirX) ? 1 : -1;
	sy = (playerScreenY < dirY) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		my_mlx_pixel_put(env, playerScreenX, playerScreenY, PLAYER_DIR_COLOR);
		if (playerScreenX == dirX && playerScreenY == dirY)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			playerScreenX += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			playerScreenY += sy;
		}
	}
	// Reset position for player dot
	playerScreenX = MINIMAP_X + MINIMAP_SIZE / 2;
	playerScreenY = MINIMAP_Y + MINIMAP_SIZE / 2;
	// Draw player dot
	for (int y = -PLAYER_DOT_SIZE / 2; y <= PLAYER_DOT_SIZE / 2; y++)
	{
		for (int x = -PLAYER_DOT_SIZE / 2; x <= PLAYER_DOT_SIZE / 2; x++)
		{
			if (x * x + y * y <= (PLAYER_DOT_SIZE / 2) * (PLAYER_DOT_SIZE / 2))
			{
				my_mlx_pixel_put(env, playerScreenX + x, playerScreenY + y,
					PLAYER_DOT_COLOR);
			}
		}
	}
}
