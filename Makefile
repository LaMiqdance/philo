NAME = philo
CC = cc -g
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
RM = rm -f
OBJS =	${SRCS:.c=.o}
SRCS = \
    philo.c \
	parsing.c \
    init/init.c \
	init/init2.c \
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