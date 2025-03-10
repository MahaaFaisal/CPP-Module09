#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	_listDuration = 0;
	_vectorDuration = 0;
	// std::cout << "PmergeMe Default Constructor\n";
}

PmergeMe::PmergeMe(int argc, char **argv)
{
	// std::cout << "PmergeMe Parameterized  Constructor\n";
	for (int i = 1; i < argc; i++)
	{
		int num;
		std::stringstream numStream(argv[i]);
		numStream >> num;
		if (numStream.fail() || !numStream.eof() || num < 0)
			throw (NotValidNumException());
		else
		{
			this->pushToContainers(num);
			// std::cout << num << " Succeeded\n";
		}
	}
}

PmergeMe::PmergeMe(PmergeMe &other)
{
	*this = other; // needs to be updated to copy containers
}

PmergeMe &PmergeMe::operator=(PmergeMe &rhs)
{
	(void)rhs; // copy containers
	return *this;
}

PmergeMe::~PmergeMe()
{
	// std::cout << "PmergeMe Destructor\n";
}

double PmergeMe::_getMicroseconds(clock_t t)
{
	clock_t duration;

	duration = clock() - t;
    return (double)duration * 1000 / CLOCKS_PER_SEC;
}

void PmergeMe::pushToContainers(int num)
{
	if (num < 0)
		throw (NotValidNumException());
	_original.push_back(num);
	_list.push_back(num);
	_vector.push_back(num);
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

	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : " << std::setprecision(5) << _vectorDuration << " us\n";
	std::cout << "Time to process a range of " << _list.size() << " elements with std::list : " << _listDuration << " us\n";
}

void PmergeMe::sortContainers()
{
	clock_t t;

	// do merge sort only
	// do insersion sort only
	t = clock();
	sort(_vector.begin(), _vector.end());
	_vectorDuration = _getMicroseconds(t);

	t = clock();
	_list.sort();
	_listDuration = _getMicroseconds(t);
	_printAfterSort();
}

const char* PmergeMe::NotValidNumException::what() const throw()
{
	return ("not an a valid number");
}
