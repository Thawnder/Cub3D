MAKEFLAGS += --silent
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_PATH = includes/Libft
LIB = -L${LIBFT_PATH} -lft -L${MINILIBX_PATH} -lmlx -lXext -lX11
LIBFT = ${LIBFT_PATH}/libft.a

MINILIBX = ${MINILIBX_PATH}libmlx.a
MINILIBX_PATH = ./includes/minilibx-linux/

FILES = main.c parsing.c parsing2.c check.c utils.c texture.c movement.c update.c minimap.c free.c

SRCS_DIR = srcs/
INCL = -I ./includes

SRCS = $(addprefix $(SRCS_DIR), $(FILES))
OBJS_EXEC = ${SRCS:.c=.o}
EXEC = cub3d


all: ${LIBFT} ${MINILIBX} ${EXEC}
	echo "\033[7;32m~| Tous les fichiers sont à jour ! |~\033[0m"\

${LIBFT}:
	@${MAKE} -sC ${LIBFT_PATH} all\
                && echo "\033[1;32m~| Compilation de la lib : OK |~\033[0m"\
                || echo "\033[1;31m~| Compilation de la lib : Erreur |~\033[0m"

${MINILIBX}:
	make -sC ${MINILIBX_PATH} \
                && echo "\033[1;32m~| Compilation de la Minilibx : OK |~\033[0m"\
                || echo "\033[1;31m~| Compilation de la Minilibx : Erreur |~\033[0m"

${EXEC}: ${OBJS_EXEC}
	${CC} ${CFLAGS} ${INCL} ${OBJS_EXEC} ${LIB} -o ${EXEC} \
		&& echo "\033[1;32m~| Compilation du $@ : OK |~\033[0m"\
		|| echo "\033[1;31m~| Compilation du $@ : Erreur |~\033[0m"

$(SRCS_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) $(INCL) -o $@ -c $<

clean:
	${MAKE} -sC ${LIBFT_PATH} fclean
	${MAKE} -sC ${MINILIBX_PATH} clean
	rm -f ${OBJS_BONUS}
	rm -f ${OBJS_EXEC}\
		&& echo "\033[1;33m~| Nettoyage des .o : OK |~\033[0m"\
		|| echo "\033[0;31m~| Compilation du $@ : Erreur |~\033[0m"

fclean: clean
	rm -f ${BONUS}
	rm -f ${EXEC} \
		&& echo "\033[1;33m~| Nettoyage des executables : OK |~\033[0m"\
		|| echo "\033[0;31m~| Compilation du $@ : Erreur |~\033[0m"

re: fclean all
