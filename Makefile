MAKEFLAGS += --silent
CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = Libft
LIB = -L${LIBFT_PATH} -lft
LIBFT = ${LIBFT_PATH}/libft.a

FILES = main.c

SRCS_DIR = srcs/
INCL = -I ./includes

SRCS = $(addprefix $(SRCS_DIR), $(FILES))
OBJS_EXEC = ${SRCS:.c=.o}
EXEC = cub3d


all: ${LIBFT} ${EXEC}
	echo "\033[7;32m~| Tous les fichiers sont à jour ! |~\033[0m"\

${LIBFT}:
	@${MAKE} -sC ${LIBFT_PATH} all\
                && echo "\033[1;32m~| Compilation de la lib : OK |~\033[0m"\
                || echo "\033[1;31m~| Compilation de la lib : Erreur |~\033[0m"

${EXEC}: ${OBJS_EXEC}
	${CC} ${CFLAGS} ${INCL} ${OBJS_EXEC} ${LIB} -o ${EXEC} \
		&& echo "\033[1;32m~| Compilation du $@ : OK |~\033[0m"\
		|| echo "\033[1;31m~| Compilation du $@ : Erreur |~\033[0m"

$(SRCS_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) $(INCL) -o $@ -c $<

clean:
	${MAKE} -sC ${LIBFT_PATH} fclean
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
