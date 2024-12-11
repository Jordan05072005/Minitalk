SRC = client.c serveur.c

CC = gcc

RM = rm -f

OBJ = ${SRC:.c=.o}

FLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

all : serv client arg

arg :
	@echo "./client 'PID Serv' 'message'"

serv : ${OBJ}
	@${CC} ${FLAGS} serveur.c libft/ft_putchar_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_strlen.c -o serv
	@gnome-terminal -- ./serv


client : ${OBJ}
	@${CC} ${FLAGS} client.c libft/ft_strlen.c libft/ft_atoi.c libft/ft_putstr_fd.c -o client

clean:
	${RM} *.o

fclean : clean
	${RM} serv client

re : fclean all clean

.PHONY: all arg serv client clean fclean re