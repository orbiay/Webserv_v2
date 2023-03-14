SRC = main.cpp http.cpp server.cpp 

CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g
CC = c++
NAME = server

all : $(NAME)
$(NAME) : $(SRC)		
		$(CC) $(CPPFLAGS) $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)
fclean : 
		rm -rf $(NAME)
re : fclean all