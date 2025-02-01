# MLX Configuration
NAME = cube3d
MLX_DIR = mlx

# Compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -Wno-unused-result 

SRCS = src/test.c
OBJS = $(SRCS:.c=.o)

UNAME_S := $(shell uname -s)
MLX_PATH = mlx

ifeq ($(UNAME_S), Linux)
    MLX_LIB = $(MLX_PATH)/libmlx_Linux.a
    MLX_FLAGS = -L$(MLX_PATH) -lmlx_Linux
    INCLUDES = -I./includes -I/usr/include -I$(MLX_PATH)
    X11_FLAGS = -L/usr/lib -lXext -lX11 -lm -lz
else
    # macOS configuration
    MLX_LIB = $(MLX_PATH)/libmlx_Darwin.a
    MLX_FLAGS = -L$(MLX_PATH) -lmlx
    INCLUDES = -I./includes -I$(MLX_PATH)
    FRAMEWORKS = -framework OpenGL -framework AppKit
endif

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