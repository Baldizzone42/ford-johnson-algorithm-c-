#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <deque>

class RPN
{
	public:
		RPN();
		~RPN();
		RPN(const RPN &copy);
		RPN &operator=(const RPN &other);
		//std::deque<RPN*> deque;
		std::deque<std::string> deque;
		std::string type;
	private:

};




#endif