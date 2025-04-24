# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 08:56:21 by ael-moha          #+#    #+#              #
#    Updated: 2025/04/24 18:24:15 by ael-moha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MLX Configuration
NAME = cube3d

# mlx dir for linux
MLX_DIR = ./mlx
# MLX VARS FOR LINUX
MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux
MLX_LIB = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux
INCLUDES = -I/usr/include -Imlx_linux -Iincludes
X11_FLAGS = -lXext -lX11 -lm -lz 


# Compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror  -g  #-O3

SRCS = src/main.c \ src/raycasting.c \ src/dda.c \ src/hooks_helper.c \ src/minimap.c \
       src/render.c \ src/render_ceiling.c \ src/render_floor.c \ src/render_wall_texture.c \
       src/efffects.c
OBJS = $(SRCS:.c=.o)

OS := $(shell uname)

all: $(NAME)
# $(info OS : $(OS))
ifeq ($(OS),Darwin)
MLX_LIB = $(MLX_DIR)/libmlx_Darwin.a
FRAMEWORKS = -framework OpenGL -framework AppKit
INCLUDES = -I$(MLX_DIR) -Iincludes
MLX_FLAGS = -L$(MLX_DIR) -lmlx $(FRAMEWORKS)
X11_FLAGS = -L/usr/X11/lib -lXext -lX11
endif

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):  $(MLX_LIB) $(OBJS)
	$(CC) $(OBJS) $(MLX_LIB) $(X11_FLAGS) -o $(NAME)

$(MLX_LIB):
	# @make -C $(MLX_DIR)

clean:
	# @make -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	# rm -f $(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re