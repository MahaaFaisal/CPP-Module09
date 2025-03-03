#ifndef __PMERGEME_HPP__
# define  __PMERGEME_HPP__

# include <iostream>
# include <sstream>
# include <vector>
# include <list>
# include <time.h>
#include <iomanip>


class PmergeMe
{
	private:
		std::vector<int> _original;
		std::list<int> _list;
		std::vector<int> _vector;
		float _listDuration;
		float _vectorDuration;
		class NotValidNumException : public std::exception
		{
			public:
				const char* what() const throw();
		};
		double _getMicroseconds(clock_t t);
		void	_printAfterSort();

	public:
		PmergeMe();
		PmergeMe(int argc, char **argv);
		PmergeMe(PmergeMe &other);
		PmergeMe &operator=(PmergeMe &rhs);
		~PmergeMe();

		void	pushToContainers(int num);
		void	printContainers();
		void	sortContainers();

};

#endif