#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>



// ================> structs <==================

typedef struct s_list
{
	char				*content;
	struct s_list		*next;
}						t_list;

typedef struct s_maplist
{
	char				*line;
	struct s_maplist	*next;
} t_maplist;

typedef struct s_mlx
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}   t_mlx;

typedef struct  s_data
{
    int i;
    int j;
    int row;
    int col;
    char **map;
}   t_data;


typedef struct s_rgb
{
    char *f;
    char *c;
}   t_rgb;


typedef struct s_textures
{
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
    t_rgb               *rgb;
    t_mlx				no_texture;
	t_mlx				so_texture;
	t_mlx				we_texture;
	t_mlx				ea_texture;
	int					c_color;
	int					f_color;
} t_textures;

typedef struct s_cub3d
{
    t_data  *my_data;
    t_textures *my_textures;
    t_mlx   mlx;
     
} t_cub3d;

// ||>--================> parssing <======================--<||
int    init_textures(t_textures *my_texts);
void parrsing_input(t_cub3d *cub, t_data *my_data, t_textures *my_textures, char *file);
int	init_data(t_data *data);
void ft_msg_error(char *msg);
int init_cub(t_cub3d *cub, t_data *my_data, t_textures *my_textures);
int	start_parser(t_cub3d *cub, t_data *data, char *path, int fd);
int	valid_texture(t_cub3d *cub, t_textures *texture, int fd);
char	*get_next_line(int fd);
int	    process_map(char **line, int fd, t_maplist **map, int *start);
int	    convert_map(t_data *data, t_maplist *m);
int	    get_colors(char *rgb);
void	ft_mapclear(t_maplist **map);
void	free_array(char **arr);
int	convert_map(t_data *data, t_maplist *m);
int	init_map(t_maplist *m, t_data *data);
void	process_line(t_data *data, t_maplist *temp);
int	process_map(char **line, int fd, t_maplist **map, int *start);
t_maplist	*check_lines(int fd, t_maplist **map);
int	check_map(t_data *data, char *path);
int	check_extension(char *exten, char *s);
int	skip_textures(char **line, int fd);
int	is_valid_characters(char *line);
t_maplist	*get_map(int fd);
void	add_map_node(t_maplist **head, char *line);
t_maplist	*create_map(char *line);
int	validate_map(t_maplist *map);
int	is_not_closed(t_maplist *prev, t_maplist *current, t_maplist *next);
int	get_biggest_line(t_maplist *head);
int	is_invalid_texture(char *str);
char	*remove_spaces(char *str);
int	set_texture_path(t_textures *texture, char *line, char *trimmed);
int	texture_path(t_textures *texture, char *line, char *trimmed);
int	parse_texture_line(t_textures *texture, char *line);
int	read_texture_lines(t_textures *texture, int fd);
int	valid_texture(t_cub3d *cub, t_textures *texture, int fd);
int	find_map(char *map);
int	ft_atoi(char *str);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void *to, const void *from, size_t n);
char	*ft_strdup(const char *src);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strspn(const char *s, const char *accept);
void	*ft_memset(void *ptr, int x, size_t n);
int	    parse_texture_line(t_textures *texture, char *line);
int	    rgb_to_int(int red, int green, int blue);
int	    check_color(char *color);
int	    parse_texture_extension(t_textures *texture);
int check_colors(t_textures *texture);
int	is_valid_rgb(char *rgb);
// ||---------------------------------------------------------||
#endif