#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	_parseDb("data.csv");
}

BitcoinExchange::BitcoinExchange(char *db)
{
	_parseDb(db);
}
BitcoinExchange::BitcoinExchange(BitcoinExchange &other)
{
	// copy the db;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange &rhs)
{
	return *this;
	// copy db as well
}

BitcoinExchange::~BitcoinExchange()
{
	// should I do something?
}

double	BitcoinExchange::_parseValue(std::string valueString)
{
	char *remaining;
	double value = strtod(valueString.c_str(), &remaining);
	if (*remaining != '\0')
		throw std::bad_exception();
	return (value);
}


void	BitcoinExchange::_parseDate(std::string date)
{
	int year;
	char delimeter1 (0);
	int month;
	char delimeter2 (0);
	int day;
	std::stringstream dateStream(date);

	if (dateStream.fail())
		throw std::bad_exception();
	std::cout << "(" << date << ")\n";
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		throw std::runtime_error("bad date format");
	// dateStream >> year >> delimeter1 >> month >> delimeter2 >> day;
	// getline(dateStream, year, '-');
	// std::cout << year << " ";
	// getline(dateStream, month, '-');
	// std::cout << month << " ";
	// getline(dateStream, day);
	// std::cout << day << " ";
}

void	BitcoinExchange::_parseDb(std::string db)
{
	std::fstream dbStream(db);
	std::string date;
	std::string xrateString;

	if (dbStream.fail())
		throw std::bad_exception();

	std::string line;
	dbStream >> line;
	if (line != "date,exchange_rate")
		throw std::bad_exception();

	while (!dbStream.eof())
	{
		getline(dbStream, date, ',');
		_parseDate(date);
		getline(dbStream, xrateString);
		std::cout << xrateString << " ";
		double xrate = _parseValue(xrateString);
		std::cout << xrate << std::endl;
		_exchangeDb[date] = xrate;
	}
}
