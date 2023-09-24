NAME = cub3D

CC = clang
CFLAGS = -Wall -Wextra -fsanitize=address -g
MLX_DIR = minilibx-linux

MLX = ${MLX_DIR}/libmlx.a

MLX_FLAG = -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit -I${MLX_DIR}

SRCS = main.c \

OBJS = ${SRCS:%.c=%.o}

%.o: %.c
	${CC} ${CFLAGS} -I${MLX_DIR} -c -o $@ $^

${NAME} : ${OBJS} ${MLX}
	${CC} ${CFLAGS} ${MLX_FLAG} ${OBJS} ${MLX} -o ${NAME}

${MLX} :
	make -C ${MLX_DIR}

all: ${NAME}

clean: 
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}
	make -C ${MLX_DIR} clean

re: fclean all

.PHONY: all clean fclean re
