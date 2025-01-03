

NAME = cube3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ./mlx

all: $(NAME)

# to be changed later
SRCS = $(wildcard src/*.c) $(wildcard src/parsing/*.c) 

OBJS = ${SRCS:.c=.o}

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	X11_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm
	MLX_LIB = $(MLX_DIR)/libmlx.a
else
	MLX_LIB =  $(MLX_DIR)/libmlx_Darwin.a
	MLXFLAGS =  -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	X11_FLAGS = -L/usr/X11/lib -lXext -lX11
endif


$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(OBJS) $(MLXFLAGS) $(X11_FLAGS) -o $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean :
	rm -f $(OBJS)

re : clean all