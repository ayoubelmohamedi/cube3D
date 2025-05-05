/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_macros.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:56:12 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/05 21:23:39 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef GAME_MACROS_H
#define GAME_MACROS_H 

#define WIDTH 640
#define HEIGHT 480

#define TILE_SIZE 64
#define FOV 60
#define MOVE_SPEED 0.1
#define M_PI 3.14159265358979323846
#define ROTATE_SPEED 0.05


#define CEILING_COLOR 0x87CEEB // Light Sky Blue
#define WALL_COLOR  0x696969 // DimGray (darker stone)
#define FLOOR_COLOR 0x8B4513

// fog 
#define FOG_COLOR 0xAAAAAA //Light Gray Fog
#define FOG_DENSITY 0.15

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307

#define KEY_LEFT 65361
#define KEY_RIGHT 65363 

// sides
#define SIDE_NORTH 0
#define SIDE_SOUTH 1
#define SIDE_EAST 2
#define SIDE_WEST 3


// map configs 
#define MINIMAP_SIZE 150
#define MINIMAP_SCALE 20     //  cell = MINIMAP_SCALE x MINIMAP_SCALE pixels
#define MINIMAP_X 10      
#define MINIMAP_Y 10
#define MINIMAP_OPACITY 0.7

#define PLAYER_DOT_SIZE 4
#define PLAYER_DOT_COLOR 0xFF0000
#define PLAYER_DIR_LENGTH 12
#define PLAYER_DIR_COLOR 0xFF0000 // red
#define PLAYER_FOV_COLOR_MINIMAP 0x90EE90 // light green

#define MINIMAP_WALL_COLOR 0x404040   // Dark gray
#define MINIMAP_FLOOR_COLOR 0x808080  // Light gray
#define MINIMAP_BORDER_COLOR 0x000000 // BLACK
#define DARK_COLOR 0x202020 



#endif