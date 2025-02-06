NAME = RPN
C++ = c++
C++_FLAGS = -Wall -Wextra -Werror -std=c++98 -g
SRC = 	main.cpp \
		RPN.cpp

OBJ_SRC = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME):$(OBJ_SRC)
	$(C++) $(C++_FLAGS) $(OBJ_SRC) -o $(NAME) 

%.o: %.cpp
	$(C++) $(C++_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_SRC)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re