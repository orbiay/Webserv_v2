
SRCS_DIR = parsing

SRCS = ft_main.cpp Webserv.cpp location.cpp Conf.cpp

OBJS = $(addprefix $(SRCS_DIR)/, $(SRCS))

SRC = main.cpp http.cpp server.cpp  parseRequest.cpp response.cpp

<<<<<<< HEAD
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g
=======
CPPFLAGS = -Wall -Wextra -Werror #-std=c++98 -fsanitize=address -g
>>>>>>> e5ac3f4c5f25913c280505365778c200eb4a655e
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
