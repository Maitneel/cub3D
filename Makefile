NAME = cub3D

CC = clang
CFLAGS = -Wall -Wextra -fsanitize=address -g

MLX_DIR = minilibx-linux
LIBFT_DIR = ./libft
GNL_DIR = ${LIBFT_DIR}/get_next_line/
SRCS_DIR = ./src
INCLUDE_DIR = ./include
DEBUG_DIR = ./debug

MLX = ${MLX_DIR}/libmlx.a
LIBFT = ${LIBFT_DIR}/libft.a

MLX_FLAG = -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit -I${MLX_DIR}

SRCS =	${SRCS_DIR}/main.c \
		${SRCS_DIR}/print_error.c \
		${SRCS_DIR}/get_graphic_info.c \
		${SRCS_DIR}/get_map.c \
		${SRCS_DIR}/init_cub3d.c \
		${SRCS_DIR}/xalloc.c \
		${SRCS_DIR}/expand_memory.c \
		${SRCS_DIR}/util_free.c \
		${SRCS_DIR}/util_free2.c \
		${SRCS_DIR}/array_size.c \
		${SRCS_DIR}/ft_isspace.c \
		${DEBUG_DIR}/debug.c \

OBJS = ${SRCS:%.c=%.o}

%.o: %.c
	${CC} ${CFLAGS} -I${INCLUDE_DIR} -I${MLX_DIR} -I${LIBFT_DIR} -I${GNL_DIR} -I ${DEBUG_DIR} -c -o $@ $^

${NAME} : ${OBJS} ${MLX} ${LIBFT}
	${CC} ${CFLAGS} ${MLX_FLAG} ${OBJS} ${MLX} ${LIBFT} -o ${NAME} 

${MLX} :
	make -C ${MLX_DIR}

${LIBFT} : ${LIBFT_DIR}/*.c
	make -C ${LIBFT_DIR}

all: ${NAME}

clean: 
	rm -rf ${OBJS}
	# make -C ${LIBFT_DIR}

fclean: clean
	rm -rf ${NAME}
	# make -C ${MLX_DIR} clean

re: fclean all

test: ${NAME}
	./${NAME} ./map/subject.cub

.PHONY: all clean fclean re
