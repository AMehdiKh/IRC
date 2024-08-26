# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 19:26:10 by ael-khel          #+#    #+#              #
#    Updated: 2024/08/25 03:22:19 by ael-khel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
NAME = ircserv
################################################################################
SRC_DIR = src

OBJ_DIR = objs

FILES = main Server Epoll Client

SRCS = ${addsuffix .cpp, $(FILES)}

OBJS = ${SRCS:%.cpp=$(OBJ_DIR)/%.o}

HEADERS = include/Server.hpp include/Epoll.hpp include/Client.hpp include/Response.hpp
################################################################################
CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g
################################################################################

.PHONY: clean
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $@ -fsanitize=address -static-libasan

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: clean all