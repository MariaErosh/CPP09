/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meroshen <meroshen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 23:17:18 by meroshen          #+#    #+#             */
/*   Updated: 2025/02/06 23:17:18 by meroshen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <cstring>
#include <limits>
#include <sys/time.h>

int main(int argc, char **argv) {
	std::vector<PmergeMe*>	elements;
	std::list<PmergeMe*>	list;
	int						num = 0;

	if (argc < 2){
		std::cerr << "Not enough arguments!" << std::endl;
		return (1);
	}

	for (int i = 1; i < argc; i++){
		for (size_t j = 0; j < strlen(argv[i]); j++){
			if (argv[i][j] == '-' && j == 0){
				std::cerr << "Error: " << argv[i] << " is negative" << std::endl;
				return (1);
			}
			if (!isdigit(argv[i][j])){
				std::cerr << "Error: " << argv[i] << " is not a number" << std::endl;
				return (1);
			}
		}
		if (atol(argv[i]) > std::numeric_limits<int>::max()){
			std::cerr << "Error: " << argv[i] << " exceed numeric limit (" << std::numeric_limits<int>::max() << ")" << std::endl;
			return (1);
		}
		elements.push_back(new PmergeMe(atoi(argv[i])));
		list.push_back(new PmergeMe(atoi(argv[i])));
		++num;
	}

	std::cout << "Before: ";
	PmergeMe::printSortedArray(elements);

	struct timeval startV, endV, startL, endL;
	gettimeofday(&startV, NULL);
	std::vector<PmergeMe*> sortedArrayV = PmergeMe::fordJohnsonSort(elements);
	gettimeofday(&endV, NULL);
	double durationV = (endV.tv_sec - startV.tv_sec) * 1e6 + (endV.tv_usec - startV.tv_usec);
	
	gettimeofday(&startL, NULL);
	std::list<PmergeMe*> sortedArrayL = PmergeMe::fordJohnsonSort(list);
	gettimeofday(&endL, NULL);
	double durationL = (endL.tv_sec - startL.tv_sec) * 1e6 + (endL.tv_usec - startL.tv_usec);

	std::cout << "After: ";
	PmergeMe::printSortedArray(sortedArrayV);

	std::cout << "Time to process a range of "<< num << " elements with std::vector: " << durationV << " us" << std::endl;
	std::cout << "Time to process a range of "<< num << " elements with std::list: " << durationL << " us" << std::endl;

	//std::cout << "Sorted array Vector: ";
	//PmergeMe::printSortedArray(sortedArrayV);

	//std::cout << "Sorted array List: ";
	//PmergeMe::printSortedArray(sortedArrayL);

	// Clean up dynamically allocated memory
	PmergeMe::cleanupElements(elements);
	PmergeMe::cleanupElements(list);

	return 0;
}
