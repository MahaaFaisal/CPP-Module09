#include "BitcoinExchange.hpp"
#include <vector>

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

double	BitcoinExchange::_parseValue(std::string valueString)
{
	std::stringstream valueStream(valueString);

	double value;

	valueStream >> std::noskipws;

	if (valueStream.fail())
		throw std::bad_exception();
	valueStream >> value;
	if (valueStream.fail() || !valueStream.eof())
		throw std::bad_exception();
	return value;

	// char *remaining;
	// double value = strtof(valueString.c_str(), &remaining);
	// if (*remaining != '\0')
	// 	throw std::bad_exception();
	// return (value);
}

void BitcoinExchange::_checkDateValidity(int year, int month, int day)
{
	int longerMonthsArr [7] = {1, 3, 5, 7, 8, 10, 12};
	std::vector<int> longerMonths(longerMonthsArr, longerMonthsArr + 7);
	// should make it check for the current date not a hardcoded value.
	if (year < 2009 || year > 2024
		|| month < 1 || month > 12
		|| day < 1 || day > 31)
		std::cerr << "Error: bad input => " << year << "-" << month << "-" << day << std::endl; 
	
	else if (std::find(longerMonths.begin(), longerMonths.end(), month) == longerMonths.end()
		&&	day == 31)
		std::cerr << "Error: bad input => " << year << "-" << month << "-" << day << std::endl; 
	else if (month == 2)
	{
		if ((year % 4 == 0 && day > 29)
			|| (year % 4 != 0 && day > 28))
		std::cerr << "Error: bad input => " << year << "-" << month << "-" << day << std::endl; 
	}
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
	_checkDateValidity(year, month, day);

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
		_exchangeDb[date] = _parseValue(xrateString);
	}
}

void BitcoinExchange::calculateValuesFile(std::string file)
{
	std::fstream dbStream(file);
	std::string date;
	std::string valueString;
	double		value;

	if (dbStream.fail())
		throw std::bad_exception();
	std::string line;
	getline(dbStream, line, '\n');
	if (line != "date | value")
		throw std::bad_exception();
	while (!dbStream.eof())
	{
		getline(dbStream, line, '\n');
		if (line.find(" | ") == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		date = line.substr(0, line.find(" | "));
		try
		{
			_parseDate(date);
			valueString = line.substr(line.find(" | ") + 3, line.length());
			value = _parseValue(valueString);
			if (value > 1000)
			{
				std::cerr << "Error: too large numebr" << std::endl;
				continue;
			}
			calculateValue(date, value);
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: bad input" << date << '\n';
		}
	}
}

void BitcoinExchange::calculateValue(std::string date, double value)
{
	// check return value of parse date
	_parseDate(date);
	if (date < "2009-01-02")
		std::cerr << "Bitcoin was not born yet at " << date << std::endl;
	else if (value < 0)
		std::cerr << "Error: not a positive number." << std::endl;
	else
	{
		std::map<std::string, float>::iterator it = _exchangeDb.begin();
		for (it = _exchangeDb.begin(); it->first < date; ++it);
		std::cout << date << " => " << value << " = " << value * it->second << std::endl;
	}
	
}