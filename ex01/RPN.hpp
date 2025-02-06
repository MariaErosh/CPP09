/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meroshen <meroshen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 23:17:26 by meroshen          #+#    #+#             */
/*   Updated: 2025/02/06 23:17:30 by meroshen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

class RPN {
	public:
		static double	calculate(std::string &expression);

		class DivisionByZero : public std::exception {
			public:
				virtual const char* what() const throw();
		};

		class invalidArgument : public std::exception {
			public:
				virtual const char* what() const throw();
		};
	
	private:
		RPN();
		~RPN();
		RPN(const RPN &src);
		RPN & operator=(RPN & src);
};