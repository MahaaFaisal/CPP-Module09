#include "PmergeMe.hpp"
# include <iostream>
# include <sstream>


int main(int argc, char **argv)
{
	// // insertion sort
	// int arr[6] = {20, 1, 2, 100, 9, 4};

	// for (int i = 1; i < 6; i++)
	// {
	// 	int key = arr[i];
	// 	int j = i - 1;

	// 	for (j  = i - 1; arr[j] > key; j--)
	// 	{
	// 		arr[j + 1] = arr[j];
	// 	}
	// 	arr[j + 1] = key;
	// }
	// for (int i = 0; i < 6; i++)
	// {
	// 	std::cout << arr[i] << " ";
	// }
// }
	try
	{
		PmergeMe sorter(argc, argv);
		sorter.sortContainers();
	}
		
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}                                                                                                                       
}
