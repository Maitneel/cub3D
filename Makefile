NAME = cub3D

CC = clang
CFLAGS = -Wall -Wextra -fsanitize=address -g
MLX_DIR = minilibx-linux
MLX_FLAG := -lmlx -framework OpenGL -framework AppKit
MLX_LOCAL_FLAG = -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit -I${MLX_DIR}

SRCS = main.c \

OBJS = ${SRCS:%.c=%.o}

%.o: %.c
	${CC} ${CFLAGS}  -c -o $@ $^

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${MLX_FLAG} ${OBJS} -o ${NAME}

all: ${NAME}

clean: 
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
