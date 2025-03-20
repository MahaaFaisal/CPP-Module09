CPP = c++
CPPFLAGS = -Wall -Wextra -Werror
SRCS = main.cpp\
		PmergeMe.cpp
NAME = PmergeMe

all: $(NAME)

$(NAME): $(SRCS)
	$(CPP) $(CPPFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean:
	rm -rf $(NAME)

re: clean all