#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _n(0), _listDuration(0), _vectorDuration(0)
{}

PmergeMe::PmergeMe(PmergeMe &other)
{
	*this = other;
}

PmergeMe &PmergeMe::operator=(PmergeMe &rhs)
{
	this->_original =  rhs._original;
	this->_list = rhs._list;
	this->_vector = rhs._vector;

	this->_listDuration = rhs._listDuration;
	this->_vectorDuration = rhs._vectorDuration;
	return *this;
}

PmergeMe::~PmergeMe()
{
	// std::cout << "PmergeMe Destructor\n";
}

double	PmergeMe::_getMicroseconds(clock_t t)
{
	clock_t duration;

	duration = clock() - t;
    return (double)duration * 1000 / CLOCKS_PER_SEC;
}

void	PmergeMe::pushToContainers(int num)
{
	if (num < 0)
		throw (NotValidNumException());
	_original.push_back(num);
	_list.push_back(num);
	_vector.push_back(num);
	_n++;
}

void	PmergeMe::printContainers()
{
	for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void	PmergeMe::_printAfterSort()
{
	std::cout << "Before: ";
	for (std::vector<int>::iterator it = _original.begin(); it != _original.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "After: ";
	for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << std::setprecision(5);
	std::cout << "Time to process a range of " << _vector.size();
	std::cout << " elements with std::vector : " << _vectorDuration << " us\n";
	std::cout << "Time to process a range of " << _list.size();
	std::cout << " elements with std::list : " << _listDuration << " us\n";
}

PmergeMe::pairsList PmergeMe::createListPairs()
{
	std::pair<int, int> current;
	pairsList listPairs;
	std::list<int>::iterator it;
	
	for (it = _list.begin()++; it != _list.end(); std::advance(it, 2))
	{
		std::list<int>::iterator next = it;
		next++;
		if (next == _list.end())
		{
			listLast = *(it);
			std::advance(it, -1);
		}
		else
		{
			current.first = *(it);
			current.second = *(next);
			listPairs.push_back(current);
		}
	}
	pairsList::iterator pit;
	return listPairs;
}

void	PmergeMe::l_sortEachPair(pairsList &listPairs)
{
	pairsList::iterator pit;
	for (pit = listPairs.begin(); pit != listPairs.end(); ++pit)
	{
		if ((*pit).first < (*pit).second)
			std::swap((*pit).first, (*pit).second);
	}
}

void	PmergeMe::l_mergeSortPairs(int begin, int end)
{

}

void	PmergeMe::_sortList()
{
	clock_t t;
	pairsList listPairs;
	std::list<int> mainChain;
	std::list<int> pend;

	t = clock();
	// recursively divide it to floor(n/2) pairs + struggler
	// doesnt have to be recursive
	listLast = -1;
	listPairs = createListPairs();
	// // sort pairs internally
	l_sortEachPair(listPairs);
	pairsList::iterator pit;
	for (pit = listPairs.begin(); pit != listPairs.end(); ++pit)
		std::cout << (*pit).first << " " << (*pit).second << '\n';
	if (listLast != -1)
		std:: cout << listLast << '\n';
	// // sort pairs externally (using merge sort)
	// l_sortPairs(&listPairs);
	
	// // create the main chain (b0 + all the a's)
	// mainChain = l_initializeMainChain(&listPairs);
	
	// // create pend (the rest of the b's)
	// pend = l_initializePend(&listPairs);
	
	// // insert b's  from pairs to main chain based on orderOfInsertion
	// // insert JacobNumber index -> go down until jacob before it.
	// l_insertPendToMainChain(&mainChain, &pend);
	
	_listDuration = _getMicroseconds(t);
}

// void	PmergeMe::_sortVector()
// {
// 	t = clock();
// 	sort(_vector.begin(), _vector.end());
// 	_vectorDuration = _getMicroseconds(t);	
// }

void	PmergeMe::sortContainers()
{
	_sortList();
	// _sortVector();
	// _printAfterSort();
}

const char* PmergeMe::NotValidNumException::what() const throw()
{
	return ("not an a valid number");
}
