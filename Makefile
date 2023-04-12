
SRCS_DIR = parsing

SRCS = ft_main.cpp Webserv.cpp location.cpp Conf.cpp

OBJS = $(addprefix $(SRCS_DIR)/, $(SRCS))

SRC = main.cpp http.cpp server.cpp  parseRequest.cpp response.cpp Get.cpp client.cpp cgi.cpp cgi_post.cpp

CPPFLAGS = -Wall -Wextra -Werror  -std=c++98 -fsanitize=address -g
CC = c++
NAME = server

all : $(NAME)

$(NAME) : $(SRC) ${OBJS}
		$(CC) $(CPPFLAGS) $(SRC) ${OBJS} -o $(NAME)

clean :
	rm -rf $(NAME)
fclean : 
		rm -rf $(NAME)
re : fclean all
