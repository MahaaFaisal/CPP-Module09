#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "the program should take one argument!\n";
		return (1);
	}

	RPN calculator;
	try
	{
		std::cout << calculator.calculateResult(argv[1]) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}