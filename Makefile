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
INCLUDES = -I./includes -Imlx

SRCS = src/main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) $(FRAMEWORKS) $(X11_FLAGS) -o $(NAME)

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