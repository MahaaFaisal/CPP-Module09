#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	std::cout << "PmergeMe Default Constructor\n";
}

PmergeMe::PmergeMe(int argc, char **argv)
{
	std::cout << "PmergeMe Parameterized  Constructor\n";
	for (int i = 1; i < argc; i++)
	{
		int num;
		std::stringstream numStream(argv[i]);
		numStream >> num;
		if (numStream.fail() || !numStream.eof() || num < 0)
		{
			std::cerr << argv[i] << " Failed\n";
			return ;
		}
		else
		{
			this->pushToContainers(num);
			std::cout << num << " Succeeded\n";
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
	std::cout << "PmergeMe Destructor\n";
}

void PmergeMe::pushToContainers(int num)
{
	_list.push_back(num);
	_vector.push_back(num);
}
void	PmergeMe::printContainers()
{
	for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	for (std::list<int>::iterator it = _list.begin(); it != _list.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}