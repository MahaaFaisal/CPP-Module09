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
		std::map<std::string, double> _exchangeDb;
		void	_parseDb(std::string db);
		void	_parseDate(std::string date);
		double	_parseValue(std::string valueString);

	public:
		BitcoinExchange();
		BitcoinExchange(char *db);
		BitcoinExchange(BitcoinExchange &other);
		BitcoinExchange &operator=(BitcoinExchange &rhs);
		~BitcoinExchange();


		// get_closest_date(the other date)
		// calculate value (date, value)
};

#endif