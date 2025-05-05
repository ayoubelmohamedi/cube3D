/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:11:40 by aez-zoui          #+#    #+#             */
/*   Updated: 2025/05/05 21:20:46 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// ================> structs <==================

typedef struct s_maplist
{
	char				*line;
	struct s_maplist	*next;
}						t_maplist;

typedef struct s_mlx
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_mlx;

typedef struct s_data
{
	int					i;
	int					j;
	int					row;
	int					col;
	char				**map;
}						t_data;

typedef struct s_rgb
{
	char				*f;
	char				*c;
}						t_rgb;

typedef struct s_textures
{
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	t_rgb				*rgb;
	t_mlx				no_texture;
	t_mlx				so_texture;
	t_mlx				we_texture;
	t_mlx				ea_texture;
	int					c_color;
	int					f_color;
}						t_textures;

typedef struct s_cub3d
{
	t_data				*my_data;
	t_textures			*my_textures;
	t_mlx				mlx;
	double				player_x;
	double				player_y;

}						t_cub3d;

int						init_texture(t_textures *my_texts);
int						init_data(t_data *data);
int						init_cub(t_cub3d *cub, t_data *my_data,
							t_textures *my_textures);
int						start_parser(t_cub3d *cub, t_data *data, char *path,
							int fd);
int						valid_texture(t_cub3d *cub, t_textures *texture,
							int fd);
char					*get_next_line(int fd);
int						process_map(char **line, int fd, t_maplist **map,
							int *start);
int						convert_map(t_data *data, t_maplist *m);
int						get_colors(char *rgb);
void					ft_mapclear(t_maplist **map);
void					free_array(char **arr);
int						check_map(t_data *data, char *path);
int						check_extension(char *exten, char *s);
int						skip_textures(char **line, int fd);
int						is_valid_characters(char *line);
t_maplist				*get_map(int fd);
void					add_map_node(t_maplist **head, char *line);
int						validate_map(t_maplist *map);
int						get_biggest_line(t_maplist *head);
int						is_invalid_texture(char *str);
char					*remove_spaces(char *str);
int						valid_texture(t_cub3d *cub, t_textures *texture,
							int fd);
int						find_map(char *map);
int						ft_atoi(char *str);
char					**ft_split(char const *s, char c);
size_t					ft_strlen(const char *str);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
void					*ft_memcpy(void *to, const void *from, size_t n);
char					*ft_strdup(const char *src);
char					*ft_strtrim(char *s1, char *set);
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
size_t					ft_strspn(const char *s, const char *accept);
void					*ft_memset(void *ptr, int x, size_t n);
int						check_color(char *color);
int						parse_texture_extension(t_textures *texture);
int						check_colors(t_textures *texture);
int						is_valid_rgb(char *rgb);
int						check_space(char c);
int						parrsing_input(t_cub3d *cub, t_data *data,
							t_textures *texture, char *file);
char					*ft_strchr(char *str, int c);

#endif
