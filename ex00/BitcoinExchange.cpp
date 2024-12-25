#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	_parseDb("data.csv", ',');
}

BitcoinExchange::BitcoinExchange(char *db)
{
	_parseDb(db, ',');
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

float	BitcoinExchange::_parseValue(std::string valueString)
{
	char *remaining;
	float value = strtof(valueString.c_str(), &remaining);
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
	char endline (0);

	std::stringstream dateStream(date);

	if (dateStream.fail())
		throw std::bad_exception();
	dateStream >> std::noskipws;
	dateStream >> year >> delimeter1 >> month >> delimeter2 >> day;
	if (dateStream.fail() || delimeter1 != '-' || delimeter2 != '-' || !dateStream.eof())
		throw std::bad_exception();
	std::cout << year << '-' << month << '-' << day << '\n'; 

}

void	BitcoinExchange::_parseDb(std::string db, char delimeter)
{
	std::fstream dbStream(db);
	std::string date;
	std::string xrateString;

	if (dbStream.fail())
		throw std::bad_exception();

	std::string line;
	getline(dbStream, line, '\n');
	if (line != "date,exchange_rate")
		throw std::bad_exception();
	while (!dbStream.eof())
	{
		getline(dbStream, date, delimeter);
		_parseDate(date);
		getline(dbStream, xrateString, '\n');
		std::cout << xrateString << " ";
		float xrate = _parseValue(xrateString);
		std::cout << xrate << std::endl;
		_exchangeDb[date] = xrate;
	}
}
