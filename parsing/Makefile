# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aomman <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/11 14:50:45 by aomman            #+#    #+#              #
#    Updated: 2023/03/11 14:53:11 by aomman           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.cpp Webserv.cpp location.cpp

NAME = webserv

all : ${NAME}

${NAME} : ${SRC}
	c++ -Wall -Wextra -Werror -std=c++98 ${SRC} -o ${NAME} -g -fsanitize=address

fclean : 
	rm -f ${NAME}

clean : fclean

re : clean all
