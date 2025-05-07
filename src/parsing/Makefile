NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -g
INCLUDES = -I/usr/local/lib
# LIBS = -lmlx_Linux -lXext -lX11 -lm -lz

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) 
#$(LIBS)

%.o: %.c parsing.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
