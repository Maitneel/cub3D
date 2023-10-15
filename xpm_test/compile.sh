#!/bin/bash

make -C ../minilibx-linux
cc -I ../minilibx-linux -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit ../minilibx-linux/libmlx.a ./print_xpm.c

