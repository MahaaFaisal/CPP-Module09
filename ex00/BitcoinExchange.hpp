#ifndef __BITCOIN__EXCHANGE__
# define __BITCOIN__EXCHANGE__

# include <fstream>
# include <sstream>
# include <map>
# include <algorithm>
# include <exception>
# include <iostream>

class BitcoinExchange
{
	private:
		std::map<std::string, float> _exchangeDb;

		void	_parseDb(std::string db, char delimeter);
		void	_parseDate(std::string date);
		double	_parseValue(std::string valueString);
		bool	_checkDateValidity(int year, int month, int day);
		std::string getClosestDate(std::string date);

	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange &other);
		BitcoinExchange &operator=(BitcoinExchange &rhs);
		~BitcoinExchange();

		void calculateValuesFile(std::string file);
		void calculateValue(std::string date,double value);
};

#endif