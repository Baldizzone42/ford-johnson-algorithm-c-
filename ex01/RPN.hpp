#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <deque>

#define GREEN   "\033[32m"
#define RED    "\033[31m"

class RPN
{
	public:
		RPN();
		~RPN();
		RPN(const RPN &copy);
		RPN &operator=(const RPN &other);
		//std::deque<RPN*> deque;
		std::deque<std::string> deque;
		std::deque<int> n;
	class zero_divide : public std::exception
	{
		public:
			const char* what() const throw();
	};
	private:

};




#endif