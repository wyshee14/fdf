#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_data {
    void    *mlx;
    void    *win;
    int     prev_x;
    int     prev_y;
    int     mouse_pressed;
}   t_data;

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define RAD_TO_DEG(x) ((x) * (180.0 / M_PI)) // Convert radians to degrees

// Function to handle mouse press
int mouse_press(int button, int x, int y, t_data *data)
{
    if (button == 1) // Left mouse button
    {
        data->mouse_pressed = 1;
        data->prev_x = x;
        data->prev_y = y;
        printf("Mouse pressed at (%d, %d)\n", x, y);
    }
    return (0);
}

// Function to handle mouse movement while pressed
int mouse_move(int x, int y, t_data *data)
{
    if (data->mouse_pressed)
    {
        int dx = x - data->prev_x;
        int dy = y - data->prev_y;

        if (dx == 0 && dy == 0)
            return (0); // No movement

        double angle = atan2(dy, dx); // Get angle in radians
        double angle_deg = RAD_TO_DEG(angle); // Convert to degrees

        printf("Mouse moved to (%d, %d), Angle: %.2f°\n", x, y, angle_deg);

        // Update previous position
        data->prev_x = x;
        data->prev_y = y;
    }
    return (0);
}

// Function to handle mouse release
int mouse_release(int button, int x, int y, t_data *data)
{
    if (button == 1) // Left mouse button released
    {
        data->mouse_pressed = 0;
        printf("Mouse released at (%d, %d)\n", x, y);
    }
    return (0);
}

// Function to close window on X button
int close_window(t_data *data)
{
    printf("Closing window...\n");
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
    return (0);
}

int main()
{
    t_data data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Mouse Angle Tracker");
    data.mouse_pressed = 0;

    // Set hooks
    mlx_hook(data.win, 4, 1L<<2, mouse_press, &data);  // Mouse press
    mlx_hook(data.win, 5, 1L<<3, mouse_release, &data); // Mouse release
    mlx_hook(data.win, 6, 1L<<6, mouse_move, &data);  // Mouse movement
    mlx_hook(data.win, 17, 0, close_window, &data); // Close window event

    mlx_loop(data.mlx);
    return (0);
}
