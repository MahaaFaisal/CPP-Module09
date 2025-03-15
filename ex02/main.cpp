#include "PmergeMe.hpp"
# include <iostream>
# include <sstream>
void	populateSorterObject(int n, char **nums, PmergeMe &sorter)
{
	for (int i = 1; i < n; i++)
	{
		int num;
		std::stringstream numStream(nums[i]);
		numStream >> num;
		if (numStream.fail() || !numStream.eof() || num < 0)
			throw (PmergeMe::NotValidNumException());
		else
			sorter.pushToContainers(num);
	}
}

int main(int argc, char **argv)
{
	try
	{
		PmergeMe sorter;
		populateSorterObject(argc, argv, sorter);
		sorter.sortContainers();
	}	
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}                                                                                                      
}
