#include "BitcoinExchange.hpp"
#include <iostream>
#include <string.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "should have only .txt argument\n";
		return (1);
	}
	try
	{
		BitcoinExchange exchange;
		exchange.calculateValuesFile(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
