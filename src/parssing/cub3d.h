#ifndef CUB3D_H
#define CUB3D_H

# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "./../get_next_line/get_next_line.h"

/*
 * parsing textures and save data 
 * 	
 * F 31,99,112
 * C 17,16,38
 * 
 *	NO textures/7itlkhr.xpm
 *	SO textures/zombie.xpm
 *	WE textures/hdskulls.xpm
 *	EA textures/flame.xpm
 *
 **/

typedef struct		s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct		s_textures_data
{
	t_rgb	*ceil_color;
	t_rgb	*floor_color;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	// map data;

}	t_textures_data;


void	check_file_map(char *file,t_textures_data *elementes_data);
void 	save_check_elements(int fd, t_textures_data *elem_dt);
void 	check_extension(char *file);
void	ft_msg_exit(char *msg);
int 	ft_strlen(char *str);
char	**ft_split(char const *s, char c);
void	free_split(char **split);



#endif /* CUB3D_H */
