


#include "../includes/cub3d.h"


void render_minimap(t_env *env, t_player *player)
{
    for (int y = 0; y < MINIMAP_SIZE; y++) {
        for (int x = 0; x < MINIMAP_SIZE; x++) {
            if (x < 2 || y < 2 || x >= MINIMAP_SIZE - 2 || y >= MINIMAP_SIZE - 2) {
                my_mlx_pixel_put(env, MINIMAP_X + x, MINIMAP_Y + y, MINIMAP_BORDER_COLOR);
                continue;
            }
            int mapX = (int)((x - MINIMAP_SIZE/2) / MINIMAP_SCALE + player->x);
            int mapY = (int)((y - MINIMAP_SIZE/2) / MINIMAP_SCALE + player->y);
            
            if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT) {
                int color = (map[mapY][mapX] > 0) ? MINIMAP_WALL_COLOR : MINIMAP_FLOOR_COLOR;
                
                int dest_color = 0x000000; 
                int r = (int)(MINIMAP_OPACITY * ((color >> 16) & 0xFF) + (1 - MINIMAP_OPACITY) * ((dest_color >> 16) & 0xFF));
                int g = (int)(MINIMAP_OPACITY * ((color >> 8) & 0xFF) + (1 - MINIMAP_OPACITY) * ((dest_color >> 8) & 0xFF));
                int b = (int)(MINIMAP_OPACITY * (color & 0xFF) + (1 - MINIMAP_OPACITY) * (dest_color & 0xFF));
                
                my_mlx_pixel_put(env, MINIMAP_X + x, MINIMAP_Y + y, (r << 16) | (g << 8) | b);
            }
            else {
                my_mlx_pixel_put(env, MINIMAP_X + x, MINIMAP_Y + y, DARK_COLOR);
            }
        }
    }
    
    int playerScreenX = MINIMAP_X + MINIMAP_SIZE / 2;
    int playerScreenY = MINIMAP_Y + MINIMAP_SIZE / 2;
    
    int dirX = playerScreenX + cos(player->dir) * PLAYER_DIR_LENGTH;
    int dirY = playerScreenY + sin(player->dir) * PLAYER_DIR_LENGTH;
    
    // Simple line drawing algorithm (Bresenham)
    int dx = abs(dirX - playerScreenX);
    int dy = abs(dirY - playerScreenY);
    int sx = (playerScreenX < dirX) ? 1 : -1;
    int sy = (playerScreenY < dirY) ? 1 : -1;
    int err = dx - dy;
    
    while (1) {
        my_mlx_pixel_put(env, playerScreenX, playerScreenY, PLAYER_DIR_COLOR);
        if (playerScreenX == dirX && playerScreenY == dirY) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            playerScreenX += sx;
        }
        if (e2 < dx) {
            err += dx;
            playerScreenY += sy;
        }
    }

    // Reset position for player dot
    playerScreenX = MINIMAP_X + MINIMAP_SIZE / 2;
    playerScreenY = MINIMAP_Y + MINIMAP_SIZE / 2;
    
    // Draw player dot
    for (int y = -PLAYER_DOT_SIZE/2; y <= PLAYER_DOT_SIZE/2; y++) {
        for (int x = -PLAYER_DOT_SIZE/2; x <= PLAYER_DOT_SIZE/2; x++) {
            if (x*x + y*y <= (PLAYER_DOT_SIZE/2)*(PLAYER_DOT_SIZE/2)) {
                my_mlx_pixel_put(env, playerScreenX + x, playerScreenY + y, PLAYER_DOT_COLOR);
            }
        }
    }
}


