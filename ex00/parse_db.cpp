#include "parse_db.hpp"
#include <fstream>


bool	parse_db(char *db)
{
	std::fstream db_stream(db);

	if (db_stream.fail())
		return (std::cerr<< "failed to open \"data.csv\"\n", 0);

	std::string line;
	db_stream >> line;
	if (line != "date,exchange_rate")
		return (std::cerr << "incorrect header\n", 0);
	
	std::string year;
	std::string month;
	std::string day;
	std::string xrate;

	while (!db_stream.eof())
	{
		getline(db_stream, year, '-');
		std::cout << year << " ";
		getline(db_stream, month, '-');
		std::cout << month << " ";
		getline(db_stream, day, ',');
		std::cout << day << " ";
		getline(db_stream, xrate);
		std::cout << xrate << std::endl;
	}

	// db_stream >> line;
	// while (db_stream >> line)
	// {
	// }
	return (1);
}
