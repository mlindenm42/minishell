# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 17:13:37 by mlindenm          #+#    #+#              #
#    Updated: 2023/09/19 17:25:14 by mlindenm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc
#CFLAGS		=	-Wall -Werror -Wextra

SRC_DIR		=	sources
OBJ_DIR		=	$(SRC_DIR)/obj

SRC_M		=	main.c err_handler.c lexsim.c free.c
SRC_P		= 	parser.c parser_utils.c testfunc.c getpath.c var_check.c
SRC_E		= 	executor.c exe_utils.c heredoc.c hdutils.c ins_outs.c expander.c
SRC_B		=	echo.c cd.c builtin_utils.c
SRC_A		=	error.c init.c lexer.c terminal.c utils.c utils_ft_split.c

SRC 		= 	$(SRC_P) $(SRC_M) $(SRC_E) $(SRC_B) $(SRC_A)

OBJ			=	$(patsubst $(SRC_DIR/*)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(SRC_DIR/*)/, $(SRC)))

LIBFT_A		=	libs/libft/libft.a
LIBFT_D		=	libs/libft

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -pthread -lreadline -L$(LIBFT_D) -lft -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT_A): make_libft

make_libft:
	make -C $(LIBFT_D)

clean:
	make fclean -C libs/libft
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
