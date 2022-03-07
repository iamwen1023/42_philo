INCS		= includes
SRC			= action.c check.c clear.c ft_atoi.c ft_isdigit.c init.c main.c utils.c
OBJ			= $(SRC:.c=.o)
NAME		= philo
FLAGS		= -Wall -Wextra -Werror -pthread -fsanitize=thread -I${INCS}
		
all: $(NAME)

$(NAME): $(OBJ)
		gcc -o $@ $(OBJ) $(FLAGS)

%.o: %.c
		cc $(FLAGS) -c $< -o $(<:.c=.o)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM)  $(NAME)

re:		fclean all

.PHONY: 	all clean fclean re