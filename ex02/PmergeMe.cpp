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

void	PmergeMe::pushToContainers(int num)
{
	if (num < 0)
		throw (NotValidNumException());
	_original.push_back(num);
	_list.push_back(num);
	_vector.push_back(num);
	_n++;
}

void	PmergeMe::sortContainers()
{
	_sortList();
	_sortVector();
	_printAfterSort();

}

double	PmergeMe::_getMicroseconds(clock_t t)
{
	clock_t duration;

	duration = clock() - t;
    return (double)duration * 1000 / CLOCKS_PER_SEC;
}

void	PmergeMe::_printAfterSort()
{
	std::cout << "Before:       ";
	for (std::vector<int>::iterator it = _original.begin(); it != _original.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "\nList After:   ";
	for (std::list<int>::iterator it = _list.begin(); it != _list.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "\nVector After: ";
	for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << std::setprecision(5);
	std::cout << "\nTime to process a range of " << _vector.size();
	std::cout << " elements with std::vector : " << _vectorDuration << " us\n";
	std::cout << "Time to process a range of " << _list.size();
	std::cout << " elements with std::list : " << _listDuration << " us\n";
}

void	PmergeMe::_sortList()
{
	clock_t t;
	pairsList listPairs;
	std::list<int> mainChain;
	std::list<int> pend;

	t = clock();
	listLast = -1;
	listPairs = createListPairs();
	l_sortEachPair(listPairs);
	l_mergeSortPairs(listPairs, 0, (_n / 2) - 1);
	mainChain = l_initializeMainChain(listPairs);
	pend = l_initializePend(listPairs);
	l_insertPendToMainChain(pend, mainChain);
	_list = mainChain;
	_listDuration = _getMicroseconds(t);
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

void	PmergeMe::l_mergeSortPairs(pairsList &listPairs, int begin, int end)
{
	if (begin >= end)
		return ;
	int	mid = (begin + end) / 2;
	l_mergeSortPairs (listPairs, begin, mid);
	l_mergeSortPairs (listPairs, mid + 1, end);
	l_merge(listPairs, begin, mid, end);
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

std::list<int>	PmergeMe::l_initializeMainChain(pairsList const &listPairs)
{
	std::list<int> mainChain;
	pairsList::const_iterator pit = std::next(listPairs.begin(), 0);

	
	mainChain.push_back((*pit).second);
	for (pit = listPairs.begin(); pit != listPairs.end(); ++pit)
		mainChain.push_back((*pit).first);
	return mainChain;
}

std::list<int>	PmergeMe::l_initializePend(pairsList const &listPairs)
{
	std::list<int> pend;

	pairsList::const_iterator pit;
	for (pit = listPairs.begin(); pit != listPairs.end(); ++pit)
		pend.push_back((*pit).second);
	return pend;
}

void	PmergeMe::l_insertPendToMainChain(std::list<int> &pend, std::list<int> &mainChain)
{
	std::list<int> insertionOrder = l_generateInsertionOrder(_n);
	std::list<int>::iterator index = insertionOrder.begin();

	for (index = insertionOrder.begin(); index != insertionOrder.end(); ++index)
	{
		if (*index >= (int)pend.size())
			continue;
		std::list<int>::iterator element = std::next(pend.begin(), *index);
		std::list<int>::iterator lowerBound = std::lower_bound(mainChain.begin(), mainChain.end(), *element);
		mainChain.insert(lowerBound, *element);
	}
	if (listLast != -1)
	{
		std::list<int>::iterator lowerBound = std::lower_bound(mainChain.begin(), mainChain.end(), listLast);
		mainChain.insert(lowerBound, listLast);
	}
}

std::list<int>	PmergeMe::l_generateInsertionOrder(int lastNum)
{
	std::list<int> insertionOrder;

	insertionOrder.push_back(3 - 1);
	insertionOrder.push_back(2 - 1);
	int first = 1;
	int second = 3;
	int next_jacob;
	for (int i = 0; second < lastNum; i++)
	{
		next_jacob = second + (2 * first);
		for (int j = next_jacob; j > second; j--)
			insertionOrder.push_back(j - 1);
		first = second;
		second = next_jacob;
	}
	return insertionOrder;
}

void	PmergeMe::_sortVector()
{
	clock_t t;
	pairsVector vectorPairs;
	std::vector<int> mainChain;
	std::vector<int> pend;

	t = clock();
	vectorLast = -1;
	vectorPairs = createVectorPairs();
	v_sortEachPair(vectorPairs);
	v_mergeSortPairs(vectorPairs, 0, (_n / 2) - 1);
	mainChain = v_initializeMainChain(vectorPairs);
	pend = v_initializePend(vectorPairs);
	v_insertPendToMainChain(pend, mainChain);
	_vector = mainChain;
	_vectorDuration = _getMicroseconds(t);
}

PmergeMe::pairsVector PmergeMe::createVectorPairs()
{
	std::pair<int, int> current;
	pairsVector vectorPairs;
	std::vector<int>::iterator it;
	
	for (it = _vector.begin()++; it != _vector.end(); std::advance(it, 2))
	{
		std::vector<int>::iterator next = it;
		next++;
		if (next == _vector.end())
		{
			vectorLast = *(it);
			std::advance(it, -1);
		}
		else
		{
			current.first = *(it);
			current.second = *(next);
			vectorPairs.push_back(current);
		}
	}
	return vectorPairs;
}

void	PmergeMe::v_sortEachPair(pairsVector &vectorPairs)
{
	pairsVector::iterator pit;
	for (pit = vectorPairs.begin(); pit != vectorPairs.end(); ++pit)
	{
		if ((*pit).first < (*pit).second)
			std::swap((*pit).first, (*pit).second);
	}
}

void	PmergeMe::v_mergeSortPairs(pairsVector &vectorPairs, int begin, int end)
{
	if (begin >= end)
		return ;
	int	mid = (begin + end) / 2;
	v_mergeSortPairs (vectorPairs, begin, mid);
	v_mergeSortPairs (vectorPairs, mid + 1, end);
	v_merge(vectorPairs, begin, mid, end);
}

void	PmergeMe::v_merge(pairsVector &vectorPairs, int begin, int mid, int end)
{
	pairsVector temp;
	pairsVector::iterator left = std::next(vectorPairs.begin(), begin);
	pairsVector::iterator midIt = std::next(vectorPairs.begin(), mid + 1);
	pairsVector::iterator right = midIt;
	pairsVector::iterator endIt = std::next(vectorPairs.begin(), end + 1);

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

	pairsVector::iterator it = std::next(vectorPairs.begin(), begin);
	for (pairsVector::iterator tempIt = temp.begin(); tempIt != temp.end(); ++tempIt)
		*(it++) = *tempIt;
}

std::vector<int>	PmergeMe::v_initializeMainChain(pairsVector const &vectorPairs)
{
	std::vector<int> mainChain;
	pairsVector::const_iterator pit = std::next(vectorPairs.begin(), 0);

	
	mainChain.push_back((*pit).second);
	for (pit = vectorPairs.begin(); pit != vectorPairs.end(); ++pit)
		mainChain.push_back((*pit).first);
	return mainChain;
}

std::vector<int>	PmergeMe::v_initializePend(pairsVector const &vectorPairs)
{
	std::vector<int> pend;

	pairsVector::const_iterator pit;
	for (pit = vectorPairs.begin(); pit != vectorPairs.end(); ++pit)
		pend.push_back((*pit).second);
	return pend;
}

void	PmergeMe::v_insertPendToMainChain(std::vector<int> &pend, std::vector<int> &mainChain)
{
	std::vector<int> insertionOrder = v_generateInsertionOrder(_n);
	std::vector<int>::iterator index = insertionOrder.begin();

	for (index = insertionOrder.begin(); index != insertionOrder.end(); ++index)
	{
		if (*index >= (int)pend.size())
			continue;
		std::vector<int>::iterator element = std::next(pend.begin(), *index);
		std::vector<int>::iterator lowerBound = std::lower_bound(mainChain.begin(), mainChain.end(), *element);
		mainChain.insert(lowerBound, *element);
	}
	if (listLast != -1)
	{
		std::vector<int>::iterator lowerBound = std::lower_bound(mainChain.begin(), mainChain.end(), listLast);
		mainChain.insert(lowerBound, listLast);
	}
}

std::vector<int>	PmergeMe::v_generateInsertionOrder(int lastNum)
{
	std::vector<int> insertionOrder;

	insertionOrder.push_back(3 - 1);
	insertionOrder.push_back(2 - 1);
	int first = 1;
	int second = 3;
	int next_jacob;
	for (int i = 0; second < lastNum; i++)
	{
		next_jacob = second + (2 * first);
		for (int j = next_jacob; j > second; j--)
			insertionOrder.push_back(j - 1);
		first = second;
		second = next_jacob;
	}
	return insertionOrder;
}


const char* PmergeMe::NotValidNumException::what() const throw()
{
	return ("not an a valid number");
}
