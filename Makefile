# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 08:56:21 by ael-moha          #+#    #+#              #
#    Updated: 2025/05/13 15:43:10 by ael-moha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3d

MLX_DIR = ./mlx

MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux
MLX_LIB = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux
INCLUDES = -I/usr/include -Imlx_linux -Iincludes -Iparsing
X11_FLAGS = -lXext -lX11 -lm -lz 


CC = cc
CFLAGS = -Wall -Wextra -Werror  -g  #-O3

SRCS_PARSER = \
    src/parsing/check_map.c \
    src/parsing/get_map.c \
    src/parsing/init_data.c \
    src/parsing/proccess_input.c \
    src/parsing/destroy_program.c \
    src/parsing/get_next_line.c \
    src/parsing/libft_func.c \
    src/parsing/read_texture.c \
    src/parsing/ft_atoi.c \
    src/parsing/get_next_line_utils.c \
    src/parsing/map_utils.c \
    src/parsing/rgb_colors.c \
    src/parsing/ft_split.c \
    src/parsing/helper.c \
    src/parsing/texture_parser.c

SRCS = src/main.c \
       src/dda.c \
       src/hooks_helper.c \
       src/render.c \
       src/render_wall_texture.c \
       src/efffects.c \
       src/texture_helpers.c \
       src/render_helpers.c \
       src/texture_helpers2.c \

OBJS = $(SRCS:.c=.o)
OBJS += $(SRCS_PARSER:.c=.o)

OS := $(shell uname)

all: $(NAME)

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