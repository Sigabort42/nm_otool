# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elbenkri <elbenkri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/21 19:49:56 by elbenkri          #+#    #+#              #
#    Updated: 2020/10/21 19:49:59 by elbenkri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_nm

NAME_OTOOL	=	ft_otool

CC		=	gcc

CFLAGS		=	-Wall -Wextra -Werror

SRCS_NM		=	./nm/main.c \
			./nm/nm.c \
			./utils/utils.c \

SRCS_OTOOL	=	./otool/main.c \
			./otool/otool.c \
			./utils/utils.c \

OBJ_NM		=	$(SRCS_NM:.c=.o)

OBJ_OTOOL	=	$(SRCS_OTOOL:.c=.o)

all: 		$(NAME)

$(NAME): 	$(OBJ_NM) $(OBJ_OTOOL)
	@make -C ./libft
	@$(CC) $(CFLAGS) $(OBJ_NM) -L./libft -lft -o $(NAME)
	@$(CC) $(CFLAGS) $(OBJ_OTOOL) -L./libft -lft -o $(NAME_OTOOL)
	@echo "\033[H\033[2J\033[32mft_nm and ft_otool [\033[32;5mCreated\033[0m\033[32m]"

clean:
	@make -C ./libft clean
	@/bin/rm -rf $(OBJ_NM)
	@/bin/rm -rf $(OBJ_OTOOL)
	@echo "\033[H\033[2J\033[32mall .o [\033[32;5mCleared\033[0m\033[32m]"

fclean:	clean
	@make -C ./libft fclean
	@/bin/rm -rf $(NAME)
	@/bin/rm -rf $(NAME_OTOOL)
	@echo "\033[H\033[2J\033[32mBinary ft_nm and ft_otool [\033[32;5mCleared\033[0m\033[32m]"

re: fclean all
