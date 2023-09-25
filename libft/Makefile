# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dummy <dummy@example.com>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 13:35:54 by dummy             #+#    #+#              #
#    Updated: 2023/09/25 14:39:25 by dummy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAG := -Wall -Wextra -Werror
RM := rm -rf
AR := ar
NAME := libft.a
BONUS_NAME := libft_bonus.a

MANDANTORY_SRCS := ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c

BONUS_SRCS := ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

GET_NEXT_LINE_SRCS = ./get_next_line/get_next_line.c \

MANDANTORY_OBJS := ${MANDANTORY_SRCS:%.c=%.o}

BONUS_OBJS := ${BONUS_SRCS:%.c=%.o}

GET_NEXT_LINE_OBJS := ${GET_NEXT_LINE_SRCS:%.c=%.o}

OBJS := ${MANDANTORY_OBJS} ${GET_NEXT_LINE_OBJS}

ifdef WITH_BONUS
	OBJS += ${BONUS_OBJS}
endif


all: ${NAME}

${NAME}: ${OBJS}
	${AR} -r ${NAME} ${OBJS}

%.o: %.c
	${CC} ${CFLAG} -c -o $@ $<

bonus: 
	@make WITH_BONUS=1

clean:
		${RM} ${MANDANTORY_OBJS} ${BONUS_OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re