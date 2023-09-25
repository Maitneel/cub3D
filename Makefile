NAME = cub3D

CC = clang
CFLAGS = -Wall -Wextra -fsanitize=address -g
MLX_DIR = minilibx-linux
LIBFT_DIR = ./libft

MLX = ${MLX_DIR}/libmlx.a
LIBFT = ${LIBFT_DIR}/libft.a

MLX_FLAG = -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit -I${MLX_DIR}

SRCS = main.c \

OBJS = ${SRCS:%.c=%.o}

%.o: %.c
	${CC} ${CFLAGS} -I${MLX_DIR} -I${LIBFT_DIR} -c -o $@ $^

${NAME} : ${OBJS} ${MLX} ${LIBFT}
	${CC} ${CFLAGS} ${MLX_FLAG} ${OBJS} ${MLX} ${LIBFT} -o ${NAME} 

${MLX} :
	make -C ${MLX_DIR}

${LIBFT} : ${LIBFT_DIR}/*.c
	make -C ${LIBFT_DIR}

all: ${NAME}

clean: 
	rm -rf ${OBJS}
	make -C ${LIBFT_DIR}

fclean: clean
	rm -rf ${NAME}
	make -C ${MLX_DIR} clean

re: fclean all

.PHONY: all clean fclean re
