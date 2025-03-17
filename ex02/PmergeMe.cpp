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
	// dont allow duplicates
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

void	PmergeMe::l_merge(pairsList &listPairs, int begin, int mid, int end)
{
	pairsList temp;
	pairsList::iterator left = std::next(listPairs.begin(), begin);
	pairsList::iterator midIt = std::next(listPairs.begin(), mid + 1);
	pairsList::iterator right = midIt;
	pairsList::iterator endIt = std::next(listPairs.begin(), end + 1);

	while (left != midIt && right != endIt)
	{
		if (*left < *right)
			temp.push_back(*(left++));
		else
			temp.push_back(*(right++));
	}

	while (left != midIt)
		temp.push_back(*(left++));

	while (right != endIt)
		temp.push_back(*(right++));

	pairsList::iterator it = std::next(listPairs.begin(), begin);
	for (pairsList::iterator tempIt = temp.begin(); tempIt != temp.end(); ++tempIt)
		*(it++) = *tempIt;
}

void	PmergeMe::l_mergeSortPairs(pairsList &listPairs, int begin, int end)
{
	if (begin >= end)
		return ;
	int	mid = (begin + end) / 2;
	l_mergeSortPairs (listPairs, begin, mid);
	l_mergeSortPairs (listPairs, mid + 1, end);
	l_merge(listPairs, begin, mid, end);
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
	// // sort pairs externally (using merge sort)
	pairsList::iterator pit;
	for (pit = listPairs.begin(); pit != listPairs.end(); ++pit)
		std::cout << (*pit).first << " " << (*pit).second << "\n";
	if (listLast != -1)
		std:: cout << listLast << '\n';
	std::cout << '\n';
	l_mergeSortPairs(listPairs, 0, (_n / 2) - 1);
	pairsList::iterator pit1;
	for (pit1 = listPairs.begin(); pit1 != listPairs.end(); ++pit1)
		std::cout << (*pit1).first << " " << (*pit1).second << '\n';
	if (listLast != -1)
		std:: cout << listLast << '\n';
	
	// // create the main chain (b0 + all the a's)
	// mainChain = l_initializeMainChain(&listPairs);
	
	// // create pend (the rest of the b's)
	// pend = l_initializePend(&listPairs);
	
	// // insert b's  from pairs to main chain based on orderOfInsertion
	// // insert JacobNumber index -> go down until jacob before it.
	// l_insertPendToMainChain(&mainChain, &pend); // using lower_bound 
	
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
