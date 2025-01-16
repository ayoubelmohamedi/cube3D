#include "./cub3d.h"

int main(int argc, char *argv[])
{
	t_textures_data *texture_dt = NULL;

	texture_dt = malloc(sizeof(t_textures_data));

	if (argc != 2 || !argv[1])
		ft_msg_exit("Error in argm\n");
	check_file_map(argv[1], texture_dt);
}
