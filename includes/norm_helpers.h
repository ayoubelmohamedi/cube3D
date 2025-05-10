


#ifndef NORM_HELPERS_H
#define NORM_HELPERS_H


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





#endif