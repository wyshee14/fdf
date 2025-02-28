#include "../include/fdf.h"

void    clear_image(t_fdf *fdf)
{
    int x;
    int y;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            my_mlx_pixel_put(fdf->img, x, y, 0x000000);
            x++;
        }
        y++;
    }
}