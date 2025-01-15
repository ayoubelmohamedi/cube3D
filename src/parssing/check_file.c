
#include "cub3d.h"

// int ft_strlen(char *str)
// {
// 	int i = 0;
// 	while (str && str[i])
// 		i++;
// 	return (i);
// }

void	ft_msg_exit(char *msg)
{
	int i;

	i = 0;
	while (msg && msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
	exit(2);
}

void check_extension(char *file)
{
	int len;

	len = ft_strlen(file);
	if (file[len - 1] != 'b' || file[len - 2] != 'u' || file[len - 3] != 'c'
			|| file[len - 4] != '.')
		ft_msg_exit("Error Extension\n");
}

void ft_printdata(char **substr)
{
	int i = 0;
	while (substr[i])
	{
		printf("%s",substr[i]);
		i++;
	}
}

void save_check_elements(int fd, t_textures_data *elem_dt)
{
	char *line;
	int len_elmet;
	char **subline;

	len_elmet = 0;
	line = get_next_line(fd);
	while (line)
	{
		//printf("%s\n",line);
		subline = ft_split(line, ' ');
		if(len_elmet == 6 && subline[0][0] == '1')
		{
		}

		// int  type = get_type_data(subline[0]);
		// 	type == 1;
		// 		color
		// 	type == 2
		// 		color
		// 	type == 3
		// 		NO textures

		//if (*line == '\n')
			// read NULL line
		// save textures data
	}

}

void	check_file_map(char *file,t_textures_data *elementes_data)
{
	int fd;
	check_extension(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_msg_exit("Error in Open file\n");
	save_check_elements(fd, elementes_data);
	close(fd);
}
