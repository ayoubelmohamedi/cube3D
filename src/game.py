import pygame
import math

# Constants
WIDTH, HEIGHT = 600, 400
GRID_SIZE = 5
TILE_SIZE = 80
FOV = math.pi / 3
NUM_RAYS = 120
MAX_DEPTH = 600

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (100, 100, 100)
BLUE = (0, 0, 255)

# Map Grid
MAP = [
    [1, 1, 1, 1, 1],
    [1, 0, 0, 0, 1],
    [1, 0, 0, 0, 1],
    [1, 0, 0, 0, 1],
    [1, 1, 1, 1, 1],
]

# Player
player_x, player_y = 2.5 * TILE_SIZE, 2.5 * TILE_SIZE
player_angle = math.pi / 4
SPEED = 4

# Initialize Pygame
pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()


def draw_map():
    for y in range(GRID_SIZE):
        for x in range(GRID_SIZE):
            rect = pygame.Rect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE)
            if MAP[y][x] == 1:
                pygame.draw.rect(screen, GRAY, rect)
            pygame.draw.rect(screen, WHITE, rect, 1)


def cast_rays():
    for ray in range(NUM_RAYS):
        ray_angle = player_angle - FOV / 2 + (ray / NUM_RAYS) * FOV

        # Ray tracing
        for depth in range(MAX_DEPTH):
            target_x = player_x + depth * math.cos(ray_angle)
            target_y = player_y + depth * math.sin(ray_angle)

            map_x = int(target_x / TILE_SIZE)
            map_y = int(target_y / TILE_SIZE)

            if 0 <= map_x < GRID_SIZE and 0 <= map_y < GRID_SIZE:
                if MAP[map_y][map_x] == 1:
                    # Calculate wall height based on distance
                    distance = depth * math.cos(ray_angle - player_angle)
                    wall_height = (TILE_SIZE / (distance + 0.0001)) * 200
                    color = (255 - min(int(distance), 255), 0, 0)

                    pygame.draw.rect(
                        screen,
                        color,
                        (
                            ray * (WIDTH / NUM_RAYS),
                            HEIGHT / 2 - wall_height // 2,
                            (WIDTH / NUM_RAYS),
                            wall_height,
                        ),
                    )
                    break


def move_player():
    global player_x, player_y, player_angle

    keys = pygame.key.get_pressed()
    if keys[pygame.K_w]:  # Move forward
        player_x += SPEED * math.cos(player_angle)
        player_y += SPEED * math.sin(player_angle)
    if keys[pygame.K_s]:  # Move backward
        player_x -= SPEED * math.cos(player_angle)
        player_y -= SPEED * math.sin(player_angle)
    if keys[pygame.K_a]:  # Turn left
        player_angle -= 0.05
    if keys[pygame.K_d]:  # Turn right
        player_angle += 0.05


# Game Loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill(BLACK)

    draw_map()
    cast_rays()
    move_player()

    pygame.display.flip()
    clock.tick(60)

pygame.quit()
