CPP = c++
CPPFLAGS = -Wall -Wextra -Werror
SRCS = main.cpp\
		RPN.cpp
NAME = RPN

all: $(NAME)

$(NAME): $(SRCS)
	$(CPP) $(CPPFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean:
	rm -rf $(NAME)

re: clean all