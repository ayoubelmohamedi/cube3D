


#ifndef NORM_HELPERS_H
#define NORM_HELPERS_H

typedef struct s_dda
{
	int		side_hit;
	int		stepX;
	int		stepY;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
}			t_dda;
typedef struct s_rays
{
    double rayDirX;
    double rayDirY;
    double *rayX;
    double *rayY;
    int 	mapX;
    int 	mapY;
} t_rays;


typedef struct s_vertical_info
{
    int x;
    int wall_height;
    double corrected_dist;
    int side;
    double rayDirX;
    double rayDirY;
    double dist;
} t_vertical_info;

typedef struct s_rgb_info
{
	int	r;
	int	g;
	int	b;
	int	ceil_r;
	int	ceil_g;
	int	ceil_b;
	int	fog_r;
	int	fog_g;
	int	fog_b;
	int	final_r;
	int	final_g;
	int	final_b;
}		t_rgb_info;

typedef struct s_texture_info {
    char	*addr;
    int		width;
    int		height;
    int		bpp;
    int		line_len;
}	t_texture_info;

typedef struct s_ceil_render
{
	double	player_dir_x;
	double	player_dir_y;
	double	plane_x;
	double	plane_y;
	int		screen_x;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	current_ceil_x;
	float	current_ceil_y;
	int		tex_x;
	int		tex_y;
}			t_ceil_render;

typedef struct s_floor_render
{
	double	player_dir_x;
	double	player_dir_y;
	double	plane_x;
	double	plane_y;
	int		screen_x;
	double	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	current_floor_x;
	float	current_floor_y;
	int		tex_x;
	int		tex_y;
}			t_floor_render;

typedef struct s_wall_render
{
	int		y_start;
	int		y_end;
	int		curr_x;
	int		corrected_dist;
	int		wall_height;
	char	*texture_addr;
	int		texture_width;
	int		texture_height;
	int		texture_bpp;
	int		texture_line_len;
	int		texX;
}			t_wall_render;

typedef struct s_texture_calc {
    int     tex_y;
    double  step;
    double  tex_pos;
    char    *dst;
    int     color;
}   t_texture_calc;


void	set_north_texture(t_player *player, t_texture_info *tex);
void	set_south_texture(t_player *player, t_texture_info *tex);
void	set_east_texture(t_player *player, t_texture_info *tex);
void	set_west_texture(t_player *player, t_texture_info *tex);


#endif