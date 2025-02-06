/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meroshen <meroshen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 23:17:23 by meroshen          #+#    #+#             */
/*   Updated: 2025/02/06 23:18:46 by meroshen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <stack>
#include <sstream>

double	RPN::calculate(std::string &expression){
	std::stack<double>	stack;
	std::istringstream	tokens(expression);
    std::string			token;
	double				num, l, r;

	while (tokens >> token){
		if ((isdigit(token[0]) && token.length() == 1) || (token[0] == '-' && isdigit(token[1]) && token.length() == 2)){
			std::istringstream stream(token);
			stream >> num;
			stack.push(num);
		}
		else{
			if (stack.size() >= 2){
				r = stack.top();
				stack.pop();
				l = stack.top();
				stack.pop();
				switch (token[0]){
					case '+' : stack.push(r + l); break;
					case '-' : stack.push(l - r); break;
					case '*' : stack.push(l * r); break;
					case '/' : if (r != 0){
									stack.push(l / r); 
									break;
								}
								else throw DivisionByZero();
				
				}
			} 
			else
				throw invalidArgument();

		}
	}
	return stack.top();
};

const char* RPN::DivisionByZero::what() const throw(){
	return ("Division by zero");
};

const char* RPN::invalidArgument::what() const throw(){
	return ("Invalid argument");
};



RPN::RPN(){};
RPN::~RPN(){};
RPN::RPN(const RPN &src){ (void)src; };
RPN & RPN::operator=(RPN & src){ (void)src; return src;};