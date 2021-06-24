NAME = libftprintf.a

LIBFT_DIR = libft
LIBFT = ${LIBFT_DIR}/libft.a

SRCS = ft_printf.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

CC = clang ${CFLAGS}

all: ${NAME}

${NAME}: ${LIBFT} ${OBJS}
	cp ${LIBFT} ${NAME}
	${AR} rcs ${NAME} ${OBJS}

${LIBFT}:
	make -C ${LIBFT_DIR}

%.o: %.c
	${CC} -I./includes -c $< -o $@

clean:
	make -C ${LIBFT_DIR} clean
	${RM} ${OBJS}

fclean: clean
	make -C ${LIBFT_DIR} fclean
	${RM} ${NAME}

re: fclean all
