NAME		= minishell
CC		= cc
CFLAGS		= -Wall -Wextra -Werror
RM		= rm -rf

SRC_DIR		= ./
OBJ_DIR		= obj/
INCLUDE		= -I . -lreadline
LIBFT_DIR	= libft/
LIBFT_LIB	= ${LIBFT_DIR}libft.a

SRCS		= $(SRC_DIR)main.c \

OBJS		= ${SRCS:${SRC_DIR}%.c=${OBJ_DIR}%.o}

all:		${OBJ_DIR} ${NAME}

${NAME}:	${OBJS} ${LIBFT_LIB} ${MLX_LIB}
			@${CC} ${CFLAGS} ${OBJS} ${LIBFT_LIB} ${INCLUDE} -o ${NAME}

${OBJ_DIR}:
			@mkdir -p ${OBJ_DIR}

${OBJ_DIR}%.o:	${SRC_DIR}%.c
			@mkdir -p ${OBJ_DIR}
			@${CC} ${CFLAGS} -I . -I ${LIBFT_DIR} -c $< -o $@

${LIBFT_LIB}:
			@echo "Building libft..."
			@make -C ${LIBFT_DIR} --no-print-directory

leakfull:
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${NAME}

clean:
			@echo "Cleaning object files..."
			@${RM} ${OBJ_DIR}
			@echo "Cleaning libft objects..."
			@make clean -C ${LIBFT_DIR} --no-print-directory

fclean:		clean
			@echo "Removing binary and libraries..."
			@${RM} ${NAME}
			@make fclean -C ${LIBFT_DIR} --no-print-directory

re:		fclean all

.PHONY:		all clean fclean re

