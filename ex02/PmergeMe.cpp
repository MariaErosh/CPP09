#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int value){
		this->value = value;
		this->left = NULL;
		this->right = NULL;
};
PmergeMe::PmergeMe(PmergeMe *left, PmergeMe *right) {
	this->value = left->value;
	this->left = left;
	this->right = right;
 };
PmergeMe::~PmergeMe(){};

PmergeMe::PmergeMe(const PmergeMe &src){
	this->value = src.value;
	this->left = src.left;
	this->right = src.right;
};

PmergeMe& PmergeMe::operator=(const PmergeMe &src){
	if (this != &src){
		this->value = src.value;
		this->left = src.left;
		this->right = src.right;
	} 
	return *this;
};

std::vector<PmergeMe*>	PmergeMe::fordJohnsonSort(std::vector<PmergeMe*>	vect){
	int	n = vect.size();
	if (n <= 1)
		return vect;		

	// 1: Split the elements into pairs and sort each pair
	std::vector<PmergeMe*> pairs;
	for (int i = 0; i < n - 1; i += 2) {
		PmergeMe* a = vect[i];
		PmergeMe* b = vect[i + 1];
		if (a->value > b->value)
			pairs.push_back(new PmergeMe(a, b));
		else 
			pairs.push_back(new PmergeMe(b, a));
	}
	
	// 2: Recursively sort the pairs
	std::vector<PmergeMe*> sortedPairs = fordJohnsonSort(pairs);

	// 3. Insert the right components
	std::vector<PmergeMe*> sortedResult;

	// 3.1. Add all left components to the sorted result
	for (unsigned int i = 0; i < sortedPairs.size(); ++i) {
		PmergeMe* current = sortedPairs[i];
		sortedResult.push_back(current->left);
	}

	// (indexes based on Jacobsthal Numbers)
	std::vector<int> jacobsthal;
	jacobsthal.push_back(0); jacobsthal.push_back(1);
	while (jacobsthal.back() < static_cast<int>(sortedPairs.size())) {
		int next_jacob = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
		jacobsthal.push_back(next_jacob);
	}

	// 3.2. Add connected right components
	unsigned int last_jacob = 0;
	unsigned int idx_insert = 0;
	for (unsigned int j = 1; j < jacobsthal.size(); ++j) {
		int current_jacob = std::min(jacobsthal[j], static_cast<int>(sortedPairs.size()));
	
		for (int i = current_jacob - 1; i >= static_cast<int>(last_jacob); --i) {
			if (i < static_cast<int>(sortedPairs.size())) {
				binaryInsert(sortedResult, sortedPairs[i]->right, i + idx_insert);
				idx_insert++;
			}
		}	
		last_jacob = current_jacob;
	}

	// If there was an odd element, add it to the result
	if (n % 2 != 0) {
		binaryInsert(sortedResult, vect[n-1], sortedResult.size()-1);
	}

	for (unsigned int i = 0; i < sortedPairs.size(); i++) {
		delete sortedPairs[i];
	}
	sortedPairs.clear();

	return sortedResult;
};

void	PmergeMe::printSortedArray(const std::vector<PmergeMe*>& elements) {
	for (unsigned int i = 0; i < elements.size(); ++i) {
		std::cout << elements[i]->value << " ";
	}
	std::cout << std::endl;
};

void PmergeMe::printSortedArray(const std::list<PmergeMe*>& elements) {
	std::list<PmergeMe*>::const_iterator iter = elements.begin();
	while (iter != elements.end()) {
		std::cout << (*iter)->value << " ";
		++iter;
	}
	std::cout << std::endl;
};

void PmergeMe::cleanupElements(std::vector<PmergeMe*>& elements) {
	for (unsigned int i = 0; i < elements.size(); i++)
		delete elements[i];
	elements.clear();
};

void PmergeMe::cleanupElements(std::list<PmergeMe*>& elements) {
	for (std::list<PmergeMe*>::iterator it = elements.begin(); it != elements.end(); ++it)
		delete *it;
	elements.clear();
};

void	PmergeMe::binaryInsert(std::vector<PmergeMe*>& sorted, PmergeMe* element, int limit) {
	int left = 0;
	int right = std::min(limit, static_cast<int>(sorted.size()));

	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (sorted[mid]->value < element->value) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	sorted.insert(sorted.begin() + left, element);
};

void	PmergeMe::binaryInsert(std::list<PmergeMe*>& sorted, PmergeMe* element, int limit) {
	std::list<PmergeMe*>::iterator left = sorted.begin();
	std::list<PmergeMe*>::iterator right = sorted.begin();

	std::advance(right, std::min(limit, static_cast<int>(sorted.size())));
	while (left != right) {
		std::list<PmergeMe*>::iterator mid = left;
		std::advance(mid, std::distance(left, right) / 2);

		if ((*mid)->value < element->value) {
			++mid;
			left = mid;
		} else {
			right = mid;
		}
	}
	sorted.insert(left, element);
};

std::list<PmergeMe*>	PmergeMe::fordJohnsonSort(std::list<PmergeMe*>	list){
	int	n = list.size();
	if (n <= 1)
		return list;		

	// 1. Split the elements into pairs and sort each pair
	std::list<PmergeMe*> pairs;
	std::list<PmergeMe*>::iterator it = list.begin();
	while (it != list.end()) {
		PmergeMe* a = *it;
		++it;
		if (it == list.end()) break;
		PmergeMe* b = *it;
		++it;
		if (a->value > b->value)
			pairs.push_back(new PmergeMe(a, b));
		else 
			pairs.push_back(new PmergeMe(b, a));
	}
	
	// 2. Recursively sort the pairs
	std::list<PmergeMe*> sortedPairs = fordJohnsonSort(pairs);

	// 3. Insert the right components
	std::list<PmergeMe*> sortedResult;

	// 3.1. Add all left components to the sorted result
	std::list<PmergeMe*>::iterator iter = sortedPairs.begin();
	while (iter != sortedPairs.end()) {
		PmergeMe* current = *iter;
		sortedResult.push_back(current->left);
		++iter;
	}

	// (indexes based on Jacobsthal Numbers)
	std::vector<int> jacobsthal;
	jacobsthal.push_back(0); jacobsthal.push_back(1);
	while (jacobsthal.back() < static_cast<int>(sortedPairs.size())) {
		int next_jacob = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
		jacobsthal.push_back(next_jacob);
	}

	// 3.2. Add all right components using binary search
	unsigned int last_jacob = 0;
	unsigned int idx_insert = 0;
	for (unsigned int j = 1; j < jacobsthal.size(); ++j) {
		int current_jacob = std::min(jacobsthal[j], static_cast<int>(sortedPairs.size()));
	
		for (int i = current_jacob - 1; i >= static_cast<int>(last_jacob); --i) {
			if (i < static_cast<int>(sortedPairs.size())) {
				std::list<PmergeMe*>::iterator it = sortedPairs.begin();
				std::advance(it, i);
				binaryInsert(sortedResult, (*it)->right, i + idx_insert);
				idx_insert++;
			}
		}	
		last_jacob = current_jacob;
	}
	// If there was an odd element, add it to the result
	if (n % 2 != 0)
		binaryInsert(sortedResult, list.back(), sortedResult.size());

	for (std::list<PmergeMe*>::iterator it = sortedPairs.begin(); it != sortedPairs.end(); ++it) {
		delete *it;
	}
	sortedPairs.clear();

	return sortedResult;
};