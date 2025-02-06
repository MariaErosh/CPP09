
#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange(std::string filePath){
	double	num;
	std::ifstream file(filePath.c_str());
	if (!file.is_open()){
		throw (FileNotOpen());
	}
	std::string	 line, dateStr, valueStr;
	std::getline(file, line);
	if (line != "date,exchange_rate")
		throw (InvalidFormat());
	
	while (std::getline(file, line)) {
		if (line.empty())
			continue;
		std::istringstream stream(line); 
		std::getline(stream, dateStr, ',');
		std::getline(stream, valueStr);

		if (!checkDateFormat(dateStr)){
			std::cout << "Error: bad input => "<< dateStr << std::endl;
			continue;
		}
		if (!checkValue(valueStr, num, false))
			continue;
		this->_db[dateStr] = num;
	}
	file.close();
};

BitcoinExchange::~BitcoinExchange(){};

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src){
	_db = src._db;
};

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src){
	if (this != &src){
		this->_db = src._db;
	}
	return (*this);
};

std::string BitcoinExchange::trim(std::string &s) {
	size_t	start = s.find_first_not_of(" \t\n");
	if (start == std::string::npos)
		return "";
	size_t	end = s.find_last_not_of(" \t\n");
	return s.substr(start, end - start + 1);
}

bool	BitcoinExchange::checkDateFormat(std::string &date){
	date = trim(date);
	if (date.length() != 10)
		return false;
	for (int i = 0; i < 10; ++i) {
		if ((i == 4 || i == 7) && date[i] != '-') return false;
		if ((i != 4 && i != 7) && !isdigit(date[i])) return false;
	}

	int month = atoi(date.substr(5, 2).c_str());
	int day = atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12) return false;
	if (day < 1 || day > 31) return false;
	return true;
};

bool	BitcoinExchange::checkValue(std::string &value, double &num, bool checkRangeNum){	
	std::istringstream	stream(value);
	stream >> num;
	if (stream.fail() || !stream.eof()){
		std::cout << "Error: bad input =>"<< value << std::endl;
		return false;
	}

	if (checkRangeNum){
		if (num < 0){
			std::cout << "Error: not a positive number."<< std::endl;
			return false;
		}
		if (num > 1000){
			std::cout << "Error: too large a number."<< std::endl;
			return false;
		}
	}
	return (true);
};

	
double	BitcoinExchange::getRate(std::string &date){
	std::map<std::string, double>::iterator	iterRes = this->_db.find(date);
	if (iterRes != this->_db.end())
		return this->_db[date];
	iterRes = this->_db.lower_bound(date);
	if (iterRes == this->_db.end() || iterRes->first != date){
		if (iterRes == this->_db.begin()){
			return 0;
		}
		else{
			iterRes--;
			return iterRes->second;
		}
	}
	return (-1);
};

void	BitcoinExchange::parcingCSVCalc(std::string filePath){
	double	num, numRes;
	std::ifstream file(filePath.c_str());
	if (!file.is_open()){
		throw (FileNotOpen());
	}
	std::string	 line, dateStr, valueStr;
	std::getline(file, line);
	if (line != "date | value" && line != "date|value")
		throw (InvalidFormat());
	
	while (std::getline(file, line)) {
		if (line.empty())
			continue;
		std::istringstream stream(line); 
		std::getline(stream, dateStr, '|');
        std::getline(stream, valueStr);

		if (!checkDateFormat(dateStr)){
			std::cout << "Error: bad input => "<< dateStr << std::endl;
			continue;
		}

		if (!checkValue(valueStr, num, true)){
			continue;
		}
		
		numRes = this->getRate(dateStr);
		if (numRes >= 0)
			std::cout << dateStr << " => " << num << " = "<< numRes * num << std::endl;
	}
	file.close();
};


const char *BitcoinExchange::InvalidFormat::what() const throw(){
	return ("Invalid Format!");
};

const char *BitcoinExchange::FileNotOpen::what() const throw(){
	return ("could not open file");
};

const char *BitcoinExchange::BadInput::what() const throw(){
	return ("Bad input");
};