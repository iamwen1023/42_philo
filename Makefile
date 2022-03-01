INCS		= includes
LIB			= libft
LIB.A		= libft.a
SRC			= basic/read_map_util_2.c basic/read_map_util.c basic/read_map.c basic/so_long.c basic/so_long_util_2.c basic/so_long_util.c
SRC_B		= bonus/read_map_util_2.c bonus/read_map_util.c bonus/read_map.c bonus/so_long.c bonus/so_long_util_2.c bonus/so_long_util.c
OBJ			= $(SRC:.c=.o)
OBJ_B		= $(SRC_B:.c=.o)
NAME		= philo
NAME_B		= philo_bonus
FLAGS		= -Wall -Wextra -Werror -I${INCS} 
OS 			= $(shell uname)

ifeq (${DEBUG}, 1)
	FLAGS	+= -g
endif

ifeq ($(OS), Linux)
	FLAGS_PLUS	= -Lmlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm
	SRC 	+= basic/destroy_linux.c
	SRC_B 	+= basic/destroy_linux.c
else
	FLAGS_PLUS	= -lmlx -framework OpenGL -framework AppKit
	SRC 	+= basic/destroy_mac.c
	SRC_B 	+= basic/destroy_mac.c
endif
		
all: $(NAME)

bonus: $(NAME_B)

$(LIB.A):
		make -C $(LIB)
		@mv $(LIB)/$(LIB.A) .

$(NAME): $(LIB.A) $(OBJ)
		gcc -o $@ $(OBJ) $(LIB.A) $(FLAGS) $(FLAGS_PLUS)

$(NAME_B): $(LIB.A) $(OBJ_B)
		gcc -o $@ $(OBJ_B) $(LIB.A) $(FLAGS) $(FLAGS_PLUS)

%.o: %.c
		cc $(FLAGS) -c $< -o $(<:.c=.o)

clean:
		$(RM) $(OBJ) $(OBJ_B) $(LIB.A)
		make clean -C $(LIB)

fclean:		clean
		$(RM)  $(NAME) $(NAME_B) $(LIB.A)
		make fclean -C $(LIB)

re:		fclean all

.PHONY: 	all clean fclean re