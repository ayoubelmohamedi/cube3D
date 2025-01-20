

#include "cub3d.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define TILE_SIZE 40
#define ROWS 10
#define COLS 19

// Define colors
#define COLOR_WALL 0xFFFFFF  // White
#define COLOR_PATH 0x000000  // Black
#define COLOR_START 0xFF0000 // Red
#define COLOR_PLAYER 0x00FF00 // Green

// Define key codes (may vary by system)
#define KEY_W 119 // Move up
#define KEY_A 97  // Move left
#define KEY_S 115  // Move down
#define KEY_D 100  // Move right
#define KEY_ESC 65307 // Exit


typedef struct s_game {
    void *mlx;
    void *win;
    int changed;
    char map[ROWS][COLS + 1];
    int player_x;
    int player_y;
} t_game;

// Function to draw a square at (x, y) with a specific color
void draw_square(t_game *game, int x, int y, int color) {
    int start_x = x * TILE_SIZE;
    int start_y = y * TILE_SIZE;

    for (int i = 0; i < TILE_SIZE; i++) {
        for (int j = 0; j < TILE_SIZE; j++) {
            mlx_pixel_put(game->mlx, game->win, start_x + i, start_y + j, color);
        }
    }
}

void draw_player(t_game *game, int color) {
    int start_x = game->player_x * (TILE_SIZE / 2);
    int start_y = game->player_y * (TILE_SIZE / 2);

    color = COLOR_START;
    printf("start_x and start_y: %d, %d\n", start_x, start_y);
    for (int i = 0; i < TILE_SIZE; i++) {
        for (int j = 0; j < TILE_SIZE; j++) {
            mlx_pixel_put(game->mlx, game->win, start_x + i, start_y + j, color);
        }
    }
}

// Function to render the map and the player
void render_map(t_game *game) {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            if (game->map[y][x] == '1') {
                draw_square(game, x, y, COLOR_WALL);
            } else if (game->map[y][x] == '0') {
                draw_square(game, x, y, COLOR_PATH);
            } else if (game->map[y][x] == 'S') {    
                // draw_square(game, x, y, COLOR_START);
                if (game->changed == 0) {
                    game->player_x = x;
                    game->player_y = y;
                    game->changed = 1;
                }
            }
        }
    }
    // Draw the player
    draw_player(game, COLOR_PLAYER);
}

// Function to handle player movement
int handle_keypress(int keycode, t_game *game) {
    int new_x = game->player_x;
    int new_y = game->player_y;
    int pressed = 0;

    printf("Key pressed: %d\n", keycode);
    if (keycode == KEY_W) 
    {
        new_y--; // Move up
        pressed = 1;
    }
    if (keycode == KEY_A)
    {
        new_x--; // Move left
        pressed = 1;
    }
    if (keycode == KEY_S)
    {
        new_y++; // Move down
        pressed = 1;
    }
    if (keycode == KEY_D)
    {
        new_x++; // Move right
        pressed = 1;
    }

    // // Check for valid movement (not walking into walls)
    if (pressed && new_x >= 0 && new_x < 720 && new_y >= 0 && new_y < 720) {
        game->player_x = new_x;
        game->player_y = new_y;
        printf("Player moved to (%d, %d)\n", game->player_x, game->player_y);

        // Redraw the map and player
        mlx_clear_window(game->mlx, game->win);
        render_map(game);
        pressed = 0;
    }
    // Exit if ESC is pressed
    if (keycode == KEY_ESC) {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    return 0;
}

int main() {
    // Initialize game structure
    t_game game = {
        .map = {
            "1111111111111111111",
            "1001001001001001001",
            "1001001001001001001",
            "1001001001001001001",
            "1001001000001001001",
            "100000000S000000001",
            "1000011111111000001",
            "1111000000000001111",
            "1000000101010000001",
            "1111111111111111111"
        }
    };
    game.changed = 0;
    // Initialize MiniLibX
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "Map with Moving Player");

    // Initial rendering of the map and player
    render_map(&game);

    // Set key press hook
    mlx_key_hook(game.win, handle_keypress, &game);

    // Run the event loop
    mlx_loop(game.mlx);

    return 0;
}
