NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
OBJS =	${SRCS:.c=.o}
SRCS = \
    philo.c \
    init/init.c \
	init/init2.c \
	parsing_management/error_and_print.c \
	parsing_management/parsing.c \
	routine/monitor_routine.c \
	routine/philo_routine.c \
    time_fcts/time_fcts.c \
    utils/utils.c \
	cleanup/cleanup.c \

all	:			$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -pthread

.o: .c
						${CC} ${CFLAGS} -c $< -o $@

clean:
						${RM} ${OBJS}
fclean: clean
						${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re