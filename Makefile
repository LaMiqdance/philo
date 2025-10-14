NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar rcs
OBJS =	${SRCS:.c=.o}
SRCS = \
    philo.c \
	parsing.c \
    init/init.c \
	init/init_utils.c \
    routine/philo_routine.c \
	routine/routine_monitor.c \
	routine/routine2.c \
	routine/routine_utils.c \
	routine/unlock_utils.c \
    time_fcts/global_time_fcts.c \
	time_fcts/time_management.c \
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