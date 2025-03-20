#include "BitcoinExchange.hpp"
#include <vector>

BitcoinExchange::BitcoinExchange()
{
	_parseDb("data.csv", ',');
}

BitcoinExchange::BitcoinExchange(BitcoinExchange &other)
{
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange &rhs)
{
	this->_exchangeDb = rhs._exchangeDb;
	return *this;
}

BitcoinExchange::~BitcoinExchange() { }

void	BitcoinExchange::_parseDb(std::string db, char delimeter)
{
	std::fstream dbStream(db.c_str());
	std::string date;
	std::string xrateString;

	if (dbStream.fail() || db.rfind(".csv") != db.length() - 4)
		throw std::ios_base::failure("Error: Failed to open db file!");

	std::string line;
	getline(dbStream, line, '\n');
	if (line != "date,exchange_rate")
		throw std::runtime_error("db header should be \"date,exchange_rate\"");
	while (!dbStream.eof())
	{
		getline(dbStream, date, delimeter);
		_parseDate(date);
		getline(dbStream, xrateString, '\n');
		_exchangeDb[date] = _parseValue(xrateString);
	}
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
		throw std::ios_base::failure("Error: Failed to open dateStream!");
	dateStream >> std::noskipws;
	dateStream >> year >> delimeter1 >> month >> delimeter2 >> day;
	if (dateStream.fail() || delimeter1 != '-' || delimeter2 != '-'
		|| !dateStream.eof())
		throw std::invalid_argument("invalid date syntax");
	if (!_checkDateValidity(year, month, day))
		throw std::invalid_argument("invalid date value");
}

bool BitcoinExchange::_checkDateValidity(int year, int month, int day)
{
	int longerMonthsArr [7] = {1, 3, 5, 7, 8, 10, 12};
	std::vector<int> longerMonths(longerMonthsArr, longerMonthsArr + 7);
	if (year < 2009 || year > 2024
		|| month < 1 || month > 12
		|| day < 1 || day > 31
		|| (std::find(longerMonths.begin(), longerMonths.end(), month) == longerMonths.end()
		&&	day == 31))
	{
		std::cout << "Error: bad input => " << year << "-" << month << "-" << day << std::endl; 
		return (0);
	}
	else if (month == 2)
	{
		if ((year % 4 == 0 && day > 29)
			|| (year % 4 != 0 && day > 28))
		{
			std::cout << "Error: bad input => " << year << "-" << month << "-" << day << std::endl;
			return (0);
		}
	}
	return (1);
}

double	BitcoinExchange::_parseValue(std::string valueString)
{
	std::stringstream valueStream(valueString);
	double value;

	valueStream >> std::noskipws;
	if (valueStream.fail())
		throw std::ios_base::failure("Error: Failed to open valueStream!");
	valueStream >> value;
	if (valueStream.fail() || !valueStream.eof())
		throw std::invalid_argument("invalid rate value");
	return value;
}

void BitcoinExchange::calculateValuesFile(std::string file)
{
	std::fstream dbStream(file.c_str());
	std::string date;
	std::string valueString;
	double		value;

	if (dbStream.fail())
		throw std::ios_base::failure("Error: Failed to open input file stream!");
	std::string line;
	getline(dbStream, line, '\n');
	if (line != "date | value")
		throw std::runtime_error("input header should be \"date | value\"");
	while (!dbStream.eof())
	{
		getline(dbStream, line, '\n');
		if (line.find(" | ") == std::string::npos)
		{
			std::cout << "Error: bad input => " << line << std::endl;
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
				std::cout << "Error: too large numebr" << std::endl;
				continue;
			}
			calculateValue(date, value);
		}
		catch(const std::exception& e)
		{
			std::cout << "Error: bad input =>" << date << '\n';
		}
	}
}

void BitcoinExchange::calculateValue(std::string date, double value)
{
	if (date < "2009-01-02")
		std::cout << "Bitcoin was not born yet at " << date << std::endl;
	else if (value < 0)
		std::cout << "Error: not a positive number." << std::endl;
	else
	{
		std::map<std::string, float>::iterator it = _exchangeDb.lower_bound(date);
		if ((*it).first != date)
			it--;
		std::cout << date << " => " << value << " = " << value * it->second << std::endl;
	}
}





