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

#include "RPN.hpp"
#include <iostream>

int main( int argc, char **argv ) {
	double	num;

	if (argc != 2){
		std::cout << "Incorrect format" <<std::endl;
		return (1);
	}
	try{
		std::string	argument = argv[1];
		num = RPN::calculate(argument);
		std::cout << num << std::endl;
	}  catch (std::exception &ex) {
		std::cerr << "Error: " << ex.what() << std::endl;
	}
	return 0;
}