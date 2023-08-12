# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 17:13:37 by mlindenm          #+#    #+#              #
#    Updated: 2023/08/12 23:37:02 by mlindenm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra

SRC_DIR		=	sources
OBJ_DIR		=	$(SRC_DIR)/obj

SRC			=	$(SRC_DIR)/error.c $(SRC_DIR)/init.c $(SRC_DIR)/lexer.c $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/utils_ft_split.c
OBJ			=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
