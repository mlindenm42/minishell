# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/13 15:23:37 by mrubina           #+#    #+#              #
#    Updated: 2023/10/17 19:37:16 by mlindenm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
# SANITIZE 	= 	-g -fsanitize=address
# SANITIZE 	= 	-LLeakSanitizer -llsan -lc++
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./minishell

SRC_DIR		=	sources
OBJ_DIR		=	$(SRC_DIR)/obj


SRC_B		=	builtin_utils.c cd.c echo.c env.c env_utils.c  export_utils.c export.c unset.c
SRC_E		= 	exe_utils.c executor.c expander.c heredoc.c ins_outs.c quote_utils.c vars.c
SRC_M		=	array_utils.c err_handler.c execute.c free_data.c main.c
SRC_P		= 	getpath.c parser_utils.c parser.c var_check.c
SRC_T		=	free_terminal.c get_next_token.c lexer.c terminal.c token.c

SRC 		= 	$(SRC_B) $(SRC_E) $(SRC_M) $(SRC_P) $(SRC_T)

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
