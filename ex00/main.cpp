#include "BitcoinExchange.hpp"
#include "parsing.hpp"

int	main(int argc, char **argv)
{
	std::string db = "data.csv";
	if (argc != 2)
	{
		std::cerr << "should have only .txt argument\n";
		return (1);
	}
	if (!parse_db())
	
	parse_input(argv[1]);
}