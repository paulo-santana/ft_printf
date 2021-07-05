NAME = libftprintf.a

SRCS_DIR = ./src
OBJS_DIR = ./obj

LIBFT_DIR = libft
LIBFT = ${LIBFT_DIR}/libft.a

SRCS_FILES = ft_printf.c specifiers.c output.c handlers_string.c \
			 handlers_char.c handlers_pointer.c handlers_intd.c \
			 handlers_inti.c handlers_intu.c handlers_hex.c \
			 handlers_hex_upper.c handlers_percentage.c

SRCS = ${addprefix ${SRCS_DIR}/, ${SRCS_FILES}}

OBJS_FILES = ${SRCS_FILES:.c=.o}
OBJS = ${addprefix ${OBJS_DIR}/, ${OBJS_FILES}}

CFLAGS = -Wall -Werror -Wextra -g3 # -fsanitize=address

CC = clang ${CFLAGS}

all: ${NAME}

${NAME}: ${LIBFT} ${OBJS}
	${RM} ${NAME}
	cp ${LIBFT} ${NAME}
	${AR} rcs ${NAME} ${OBJS}

${LIBFT}:
	make -C ${LIBFT_DIR}

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	${CC} -I./includes -c $< -o $@

test: ${NAME}
	${CC} main.c -fsanitize=address -L./ -lftprintf
	./a.out

clean:
	make -C ${LIBFT_DIR} clean
	${RM} ${OBJS}

fclean: clean
	make -C ${LIBFT_DIR} fclean
	${RM} ${NAME}

re: fclean all

.PHONY: ${LIBFT}
