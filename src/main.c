#include "cub3d.h"


void my_put_pixel(void *mlx, void *win, int x, int y, Color color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        int rgb = (color.r << 16) | (color.g << 8) | color.b;
        mlx_pixel_put(mlx, win, x, y, rgb);
    }
}
// (x−cx)^2+(y−cy)^2+(z−cz)^2=r^2
void draw_sphere(void *mlx, void *win, Vector3 center, int radius, Color color) {
    for (int y = center.y - radius; y <= center.y + radius; y++) {
        for (int x = center.x - radius; x <= center.x + radius; x++) {
            int dx = x - center.x;
            int dy = y - center.y;
            if (dx * dx + dy * dy <= radius * radius) {
                my_put_pixel(mlx, win, x, y, color);
                // usleep(100);
            }
        }
    }
}

void parse_map(const char *filename, int map[MAX_HEIGHT][MAX_WIDTH], int *width, int *height) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char line[MAX_WIDTH + 2]; // +2 for newline and null terminator
    int row = 0;

    while (fgets(line, sizeof(line), file)) {
        int col = 0;
        printf("LINE\n");
        for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++) {
            if (line[i] == '1' || line[i] == '0' || line[i] == 'S') {
                map[row][col++] = line[i] - '0'; // Convert char to int
            }
        }
        // Fill the rest of the row with null (0) to ensure it's properly terminated
        while (col < MAX_WIDTH) {
            map[row][col++] = 0;
        }
        row++;
    }
    *width = MAX_WIDTH;
    *height = row; // Set height to the number of rows read
    fclose(file);
}


void draw_square(void *mlx, void *win, int x, int y, int color) {
    printf("drawing a square\n");
    for (int i = 0; i < TILE_SIZE; i++) {
        for (int j = 0; j < TILE_SIZE; j++) {
            mlx_pixel_put(mlx, win, x + i, y + j, color);
        }
    }
}

void draw_map(int map[MAX_HEIGHT][MAX_WIDTH], void *mlx, void *win)
{
    int color;
  for (int y = 0; y < MAX_HEIGHT; y++) {
        for (int x = 0; x < MAX_WIDTH; x++) {
            color = 0xFFFFFF; 
            if (map[y][x] == 1 || map[y][x] == 0)
                color = (map[y][x] == 1) ? 0xFFFFFF : 0x000000; // Wall: white, Floor: black
            else
                color = 0x00FF00; // green 
            draw_square(mlx, win, x * TILE_SIZE, y * TILE_SIZE, color);
        }
    }
}
int main(int ac, char *av[])
{
    void    *mlx;        
    void    *win;
    (void)ac;
    (void)av;
    mlx = mlx_init();
    if (!mlx)
    {
        // (void*)write(2, "Error: Unable to initialize MinilibX\n", 37);
        return (1);
    }
    win = mlx_new_window(mlx, WIDTH, HEIGHT, "2D Sphere in MLX");
    if (!win)
    {
        // (void*)write(2, "Error: Unable to create window\n", 31);
        return (1);
    }
  
    // Vector3 sphere_center = {WIDTH / 2, HEIGHT / 2, 0};
    // int sphere_radius = 300;
    // Color sphere_color = {255, 77, 0}; // Red color
    // draw_sphere(mlx, win, sphere_center, sphere_radius, sphere_color);
    // Wait for events (close window with any key press)
    int map[MAX_HEIGHT][MAX_WIDTH];
    int width, height;
    parse_map("./maps/good/map_only.cub",map, &width, &height);

    size_t i = 0, j = 0;
    while (i < MAX_HEIGHT) {
        for (j = 0; j < MAX_WIDTH; j++) { // Iterate over all columns
            printf("%d ", map[i][j]);    // Print each value, including 0
        }
        printf("\n"); // Move to the next line after printing a row
        i++;
    }

    draw_map(map, mlx, win);
    mlx_loop(mlx);
    return (0);
}