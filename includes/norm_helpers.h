


#ifndef NORM_HELPERS_H
#define NORM_HELPERS_H


typedef struct s_rays
{
    double rayDirX;
    double rayDirY;
    double *rayX;
    double *rayY;
    int *mapX;
    int *mapY;
} t_rays;


typedef struct s_vertical_info
{
    int x;
    int wall_height;
    double corrected_dist;
    int side;
} t_vertical_info;




#endif