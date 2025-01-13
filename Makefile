NAME = cube3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ./mlx

SRCS = $(wildcard src/*.c) $(wildcard src/parsing/*.c)
OBJS = ${SRCS:.c=.o}

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
    MLX_FLAGS = -L$(MLX_DIR) -lmlx
    X11_FLAGS = -lXext -lX11 -lm
else
    MLX_LIB = $(MLX_DIR)/libmlx_Darwin.a
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
    X11_FLAGS = -L/usr/X11/lib -lXext -lX11
endif

all: $(MLX_LIB) $(NAME)

%.o: %.c
    $(CC) $(CFLAGS) -I./includes -I$(MLX_DIR) -c $< -o $@

$(NAME): $(OBJS)
    $(CC) $(OBJS) $(MLX_FLAGS) $(X11_FLAGS) -o $(NAME)

$(MLX_LIB):
    @make -C $(MLX_DIR)

clean:
    @make -C $(MLX_DIR) clean
    rm -f $(OBJS)

fclean: clean
    rm -f $(NAME)
    rm -f $(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re