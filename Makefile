NAME = cub3D

CC = clang
CFLAGS = -Wall -Wextra 
MLX_DIR = minilibx-linux

HOSTNAME = ${shell hostname | sed 's/c[0-9]*r[0-9]*s[0-9]\.//g'}

ifeq (${HOSTNAME}, "42tokyo.jp")
	MLX_FLAG := -lmlx -framework OpenGL -framework AppKit
else 
	MLX_FLAG = -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit -I${MLX_DIR}
endif

SRCS = main.c \

OBJS = ${SRCS:%.c=%.o}

%.o: %.c
	${CC} ${CFLAGS} ${MLX_FLAG} -c -o $@ $^

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${MLX_FLAG} ${OBJS} -o ${NAME} ${MLX_DIR}/libmlx.a

all: ${NAME}

clean: 
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
