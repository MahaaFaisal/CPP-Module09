CPP = c++
CPPFLAGS = -Wfatal-errors #-Wall -Wextra -Werror
SRCS = main.cpp\
		RPN.cpp
NAME = RPN

all: $(NAME)

$(NAME): $(SRCS)
	$(CPP) $(CPPFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(NAME)

re: clean all