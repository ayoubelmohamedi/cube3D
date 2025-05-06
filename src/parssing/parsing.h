/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:43:15 by ayel-mou          #+#    #+#             */
/*   Updated: 2025/05/06 23:07:35 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 1
typedef struct s_list
{
	char				*content;
	struct s_list		*next;
}						t_list;

typedef struct s_maplist
{
	char				*line;
	struct s_maplist	*next;
}						t_maplist;

typedef struct s_rgb
{
	char				*f;
	char				*c;
}						t_rgb;

typedef struct s_texture
{
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	t_rgb				*rgb;
	int					c_color;
	int					f_color;
}						t_texture;

typedef struct s_data
{
	char				**map;
	int					row;
	int					col;
	int					j;
	int					i;
}						t_data;

typedef struct s_cub
{
	float				player_x;
	float				player_y;
	float				p_angle;
	int					pixel_size;
	t_data				*data;
	t_texture			*texture;
} t_cub;

int			proccess_input(t_data *data, t_cub *cub, char *path,
				t_texture *texture);
int			init_texture(t_texture *texture);
int			init_data(t_data *data);
int			init_cub(t_cub *cub, t_data *data, t_texture *texture);
int			ft_atoi(char *str);
char		**ft_split(char const *s, char c);
char		*get_next_line(int fd);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memcpy(void *to, const void *from, size_t n);
char		*ft_strdup(const char *src);
char		*ft_strtrim(char const *s1, char const *set);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strspn(const char *s, const char *accept);
int			check_space(char c);
int			newline_checker(t_list *list);
int			llist(t_list *list);
void		copy_the_list(t_list *list, char *the_line);
void		dealloc(t_list **list, t_list *clean_node, char *buf);
char		*ft_strchr(const char *s, int c);
int			valid_texture(t_cub *cub, t_texture *texture, int fd);
int			is_valid_rgb(char *rgb);
int			check_colors(t_texture *texture);
int			parse_texture_extension(t_texture *texture);
int			read_texture_lines(t_texture *texture, int fd);
int			parse_texture_line(t_texture *texture, char *line);
int			texture_path(t_texture *texture, char *line, char *trimmed);
int			set_texture_path(t_texture *texture, char *line, char *trimmed);
void		free_array(char **arr);
int			check_extension(char *exten, char *s);
t_maplist	*create_map(char *line);
void		add_map_node(t_maplist **head, char *line);
int			skip_textures(char **line, int fd);
int			is_valid_characters(char *line);
int			init_map(t_maplist *m, t_data *data);
int			convert_map(t_data *data, t_maplist *m);
int			is_not_closed(t_maplist *prev, t_maplist *current, t_maplist *next);
int			validate_map(t_maplist *map);
int			convert_map(t_data *data, t_maplist *m);
void		process_line(t_data *data, t_maplist *temp);
t_maplist	*get_map(int fd);
int			get_biggest_line(t_maplist *head);
void		ft_mapclear(t_maplist **map);
void		*ft_memset(void *ptr, int x, size_t n);
void		destroy_all(t_cub *cub);
void		destroy_data(t_data *data, t_texture *texture);
int			process_map(char **line, int fd, t_maplist **map, int *start);
t_maplist	*check_lines(int fd, t_maplist **map);
int			is_invalid_texture(char *str);
void		free_heap(t_cub *cub);
char		*remove_spaces(char *str);
int			find_map(char *map);
int	ft_exit(t_cub *cub);

#endif