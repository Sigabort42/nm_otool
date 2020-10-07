NAME		=	ft_nm

NAME_OTOOL	=	ft_otool

CC		=	clang

CFLAGS		=	-Wall -Wextra -Werror

SRCS_NM		=	./nm/main.c \
			./nm/nm.c \

SRCS_OTOOL	=

OBJ_NM		=	$(SRCS_NM:.c=.o)

OBJ_OTOOL	=	$(SRCS_OTOOL:.c=.o)

all: 		$(NAME)

$(NAME): 	$(OBJ_NM) $(OBJ_OTOOL)
	@make -C ./libft
	@$(CC) $(CFLAGS) $(OBJ_NM) -L./libft -lft -o $(NAME)
	@echo "\033[H\033[2J\033[32mft_nm and ft_otool [\033[32;5mCreated\033[0m\033[32m]"

clean:
	@make -C ./libft clean
	@/bin/rm -rf $(OBJ_NM)
	@echo "\033[H\033[2J\033[32mall .o [\033[32;5mCleared\033[0m\033[32m]"

fclean:	clean
	@make -C ./libft fclean
	@/bin/rm -rf $(NAME)
	@echo "\033[H\033[2J\033[32mBinary ft_nm and ft_otool [\033[32;5mCleared\033[0m\033[32m]"

re: fclean all
