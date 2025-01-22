#ifndef __PMERGEME_HPP__
# define  __PMERGEME_HPP__

# include <iostream>
# include <sstream>
# include <vector>
# include <list>

class PmergeMe
{
	private:
		std::list<int> _list;
		std::vector<int> _vector;

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