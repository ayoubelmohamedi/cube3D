

#include "../includes/cub3d.h"


int main(int ac, char *av[])
{

    void    *mlx;        
    void    *win;
    (void)ac;
    (void)av;

    mlx = mlx_init();
    if (!mlx)
    {
        write(2, "Error: Unable to initialize MinilibX\n", 37);
        return (1);
    }

    win = mlx_new_window(mlx, 800, 600, "My Window");
    if (!win)
    {
        write(2, "Error: Unable to create window\n", 31);
        return (1);
    }

    // Wait for events (close window with any key press)
    mlx_loop(mlx);

    return (0);
}   