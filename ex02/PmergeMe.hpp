#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>

class PmergeMe {
	private:
		int			value;
		PmergeMe*	left;
		PmergeMe*	right;

	public:
		PmergeMe(int value);
		PmergeMe(PmergeMe *left, PmergeMe *right);
		~PmergeMe();
		PmergeMe(const PmergeMe &src);
		PmergeMe& operator=(const PmergeMe &src);

		static void binaryInsert(std::vector<PmergeMe*>& sorted, PmergeMe* element, int limit);
		static void binaryInsert(std::list<PmergeMe*>& sorted, PmergeMe* element, int limit);
		
		static std::vector<PmergeMe*>	fordJohnsonSort(std::vector<PmergeMe*>	vect);
		static std::list<PmergeMe*>	fordJohnsonSort(std::list<PmergeMe*>	list);

		
		static void printSortedArray(const std::vector<PmergeMe*>& elements);
		static void printSortedArray(const std::list<PmergeMe*>& elements);
		
		static void cleanupElements(std::vector<PmergeMe*>& elements);
		static void cleanupElements(std::list<PmergeMe*>& elements);

};


