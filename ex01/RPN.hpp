#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

class RPN
{
	public:
		RPN();
		~RPN();
		RPN(const RPN &copy);
		RPN &operator=(const RPN &other);
		void polish_calculator();
		std::vector<std::string>polish;
		void calculate(std::vector<std::string>::iterator it, char c, int i);
	private:


};




#endif