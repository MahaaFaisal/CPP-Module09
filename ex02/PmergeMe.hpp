#ifndef __PMERGEME_HPP__
# define  __PMERGEME_HPP__

# include <iostream>
# include <sstream>
# include <vector>
# include <list>
# include <time.h>
# include <iomanip>
# include <utility>
# include <algorithm>

class PmergeMe
{
	private:
		int _n;
		std::vector<int> _original;
		double _getMicroseconds(clock_t t);
		void	_printAfterSort();

		std::list<int> _list;
		float _listDuration;
		typedef std::list<std::pair<int, int> > pairsList;
		int	listLast;
		void		_sortList();
		pairsList	createListPairs();
		void		l_sortEachPair(pairsList &listPairs);
		void		l_mergeSortPairs(pairsList &listPairs, int begin, int end);
		void		l_merge(pairsList &listPairs, int begin, int mid, int end);
		std::list<int>	l_initializeMainChain(pairsList const &listPairs);
		std::list<int>	l_initializePend(pairsList const &listPairs);
		void		l_insertPendToMainChain(std::list<int> &pend, std::list<int> &mainChain);
		std::list<int>	l_generateInsertionOrder(int lastNum);


		std::vector<int> _vector;
		float _vectorDuration;
		typedef std::vector<std::pair<int, int> > pairsVector ;
		int	vectorLast;
		void		_sortVector();
		pairsVector	createVectorPairs();
		void		v_sortEachPair(pairsVector &vectorPairs);
		void		v_mergeSortPairs(pairsVector &vectorPairs, int begin, int end);
		void		v_merge(pairsVector &vectorPairs, int begin, int mid, int end);
		void				v_insertPendToMainChain(std::vector<int> &pend, std::vector<int> &mainChain);
		std::vector<int>	v_initializeMainChain(pairsVector const &vectorPairs);
		std::vector<int>	v_initializePend(pairsVector const &listVector);
		std::vector<int>	v_generateInsertionOrder(int lastNum);

	public:
		PmergeMe();
		PmergeMe(PmergeMe &other);
		PmergeMe &operator=(PmergeMe &rhs);
		~PmergeMe();

		void	pushToContainers(int num);
		void	sortContainers();

		class NotValidNumException : public std::exception
		{
			public:
				const char* what() const throw();
		};

};

#endif