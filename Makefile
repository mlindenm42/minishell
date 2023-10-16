# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/13 15:23:37 by mrubina           #+#    #+#              #
#    Updated: 2023/10/17 00:46:20 by mlindenm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc
# CFLAGS		=	-Wall -Werror -Wextra
SANITIZE 	= 	-g -fsanitize=address
# SANITIZE 	= 	-LLeakSanitizer -llsan -lc++
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./minishell

SRC_DIR		=	sources
OBJ_DIR		=	$(SRC_DIR)/obj

SRC_M		=	main.c err_handler.c free.c array_utils.c execute.c
SRC_P		= 	parser.c parser_utils.c testfunc.c getpath.c var_check.c
SRC_E		= 	executor.c exe_utils.c heredoc.c hdutils.c ins_outs.c expander.c vars.c
SRC_B		=	echo.c cd.c builtin_utils.c export.c env.c unset.c export_sort.c
SRC_T		=	free_terminal.c get_next_token.c lexer.c terminal.c token.c
SRC_G		=	dump.c garbage_truck.c

SRC 		= 	$(SRC_P) $(SRC_M) $(SRC_E) $(SRC_B) $(SRC_T) $(SRC_G)

OBJ 		= 	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LIBFT_A		=	libs/libft/libft.a
LIBFT_D		=	libs/libft

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ)
	cc -o $(NAME) -g $(SANITIZE) $(OBJ) -lreadline -L$(LIBFT_D) -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c | $(OBJ_DIR)
	$(CC) -g $(CFLAGS) -c $< -o $@

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
