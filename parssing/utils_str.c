#include "cub3d.h"

void ft_msg_error(char *msg)
{
    int i;

    i = 0;
    while (msg[i])
    {
        write(1, &msg[i], 1);
        i++;
    }
}