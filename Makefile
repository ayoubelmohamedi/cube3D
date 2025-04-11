# MLX Configuration
NAME = cube3d
MLX_DIR = mlx/
MLX_LIB =  $(MLX_DIR)libmlx_Darwin.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx
FRAMEWORKS = -framework OpenGL -framework AppKit
X11_FLAGS = -L/usr/X11/lib -lXext -lX11

# Compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3

# Add MLX include path
INCLUDES = -I/usr/include -Imlx_linux 

SRCS = src/main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz  -o $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	# @make -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	# rm -f $(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re