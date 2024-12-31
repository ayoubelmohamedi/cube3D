

NAME = cube3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ./mlx

# to be changed later
SRCS = $(wildcard src/*.c)

OBJS = ${SRCS:.c=.o}


ifeq ($(OS), Linux)
	X11_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm
	MLX_LIB = $(MLX_DIR)/libmlx.a
else
	MLX_LIB =  $(MLX_DIR)/libmlx_Darwin.a
	MLXFLAGS =  -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	X11_FLAGS = -L/usr/X11/lib -lXext -lX11
endif


$(NAME): $(MLX_LIB) $(OBJ)
	$(CC) $(OBJ) $(MLXFLAGS) $(X11_FLAGS) -o $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean :
	rm -f $(OBJ)