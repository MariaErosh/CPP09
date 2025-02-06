#pragma once
#include <map>
#include <string>

class BitcoinExchange {
private:
	std::map<std::string, double>	_db;

	static bool			checkDateFormat(std::string &date);
	static bool			checkValue(std::string &value, double &num, bool checkRangeNum);
	static std::string	trim(std::string &s);

public:
	BitcoinExchange(std::string filePath);
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &src);
	BitcoinExchange &operator=(const BitcoinExchange &src);	
	
	double			getRate(std::string &date);
	void			parcingCSVLoad(std::string &filePath);
	void			parcingCSVCalc(std::string filePath);
	
	
	class FileNotOpen : public std::exception {
		public:
			virtual const char *what() const throw();
	};

	class InvalidFormat : public std::exception {
		public:
			virtual const char *what() const throw();
	};

	class BadInput : public std::exception {
		public:
			virtual const char *what() const throw();
	};

};