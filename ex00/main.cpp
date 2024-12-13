#include "BitcoinExchange.hpp"
#include "parsing.hpp"
#include <iostream>
#include <string.h>

void	play_with_maps()
{

	std::map<std::string, int> mp;

	mp["Sara"] = 1;
	mp["Maha"] = 10;
	mp["Dina"] = 5;

	std::map<std::string, int>::iterator it = mp.begin();
	for (it = mp.begin(); it != mp.end(); ++it)
	{
		std::cout << "key: " << it->first;
		std::cout << "Value: " << it->second << std::endl;
	}
}

int	main(int argc, char **argv)
{
	(void)argv;

	char db[] = "data.csv";

	if (argc != 2)
	{
		std::cerr << "should have only .txt argument\n";
		return (1);
	}
	try
	{
		BitcoinExchange exchange;
		// parse_input(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}
