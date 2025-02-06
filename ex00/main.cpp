/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meroshen <meroshen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:32:23 by meroshen          #+#    #+#             */
/*   Updated: 2025/01/15 12:23:50 by meroshen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main( int argc, char **argv ) {
	
	(void)argv;
	if (argc != 2){
		std::cout << "Incorrect format" <<std::endl;
		return (1);
	}
	try{
		BitcoinExchange	test("data.csv");	
		test.parcingCSVCalc(argv[1]);
	}  catch (std::exception &ex) {
		std::cout << "Error: " << ex.what() << std::endl;
	}
	return 0;
}