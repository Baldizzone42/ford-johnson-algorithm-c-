/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:54:56 by jormoral          #+#    #+#             */
/*   Updated: 2025/05/09 19:28:42 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int op(char c){
	char op[4] = {'+', '-', '/', '*'};
	for(int i = 0; i < 4; i++){
		if(c == op[i])
			return 1;
	}
	return 0;
}

int checkinit(std::string input)
{
	for(int i = 0; input[i]; i++)
	{
		if((input[i] >= '0' && input[i] <= '9') || input[i] == ' ' || op(input[i]))
			continue;
		else
			return (std::cerr << RED << "invalid character\n"), 1;
	}
	return 0;
}

void insert_input(RPN *main, std::string input)
{
	
	int i  = 0;
	int j = 0;
	while(input[i])
	{
		while(input[j] && input[j] == ' ')
			j++;
		i = j;
		while(input[j] && input[j] != ' ')
			j++;
		if(i != j)
		{
			std::string temp = input.substr(i, j - i);
			main->deque.push_back(temp);
		}
	}
}

int check_number(const char *s)
{
	int i = 0;
	while(s[i])
	{
		if(s[i] >= '0' && s[i] <= '9')
			i++;
		else
			return 0;
	}
	return 1;
}

int checkn(RPN *main)
{
	std::deque<std::string>::iterator it = main->deque.begin();
	std::deque<std::string>::iterator itend = main->deque.end();
	int n = 0;
	int opn = 0;
	while(it != itend)
	{
		if((check_number((*it).c_str())))
			n++;
		if(op((*it).c_str()[0]))
			opn++;
		it++;
	}
	if((n - 1) == opn && main->deque.size() > 2)
		return 1;
	else
		return (std::cout << RED << "Error: Operator problems" << std::endl), 0;
}

int check_rown(RPN *main)
{
	std::deque<std::string>::iterator it = main->deque.begin();
	std::deque<std::string>::iterator itend = main->deque.end();
	int n = 0;
	int opn = 0;
	int flag = 0;
	while(it != itend || flag < 1)
	{
		if((check_number((*it).c_str())))
			n++;
		if(op((*it).c_str()[0]) && n > opn)
			opn++,flag = 1;
		else 
			flag = 2;
		it++;
	}
	if((n - 1) == opn && main->deque.size() > 2)
		return 1;
	else
		return (std::cout << RED << "Error: Wrong Row of numbers" << std::endl), 0;
}


void print_dequestd(RPN *main)
{
	std::deque<std::string>::iterator it = main->deque.begin();
	std::deque<std::string>::iterator itend = main->deque.end();
	while(it != itend)
	{
		std::cout  << GREEN << (*it)<< " ";
		it++;
	} 
	std::cout << std::endl;
}

void print_dequeint(RPN *main)
{
	std::deque<int>::iterator it = main->n.begin();
	std::deque<int>::iterator itend = main->n.end();
	while(it != itend)
	{
		std::cout  << GREEN << (*it)<< " ";
		it++;
	} 
	std::cout << std::endl;
}

const char *RPN::zero_divide::what() const throw()
{
	return "Good try bro\n";
}

int operate(RPN *main, char c)
{
	if(c == '-')
		return (main->n[1] - main->n[0]);
	if(c == '+')
		return (main->n[1] + main->n[0]);
	if(c == '/')
	{
		if(main->n[0] != 0)
			return (main->n[1] / main->n[0]);
		else
			throw(RPN::zero_divide());
	}
	if(c == '*')
		return (main->n[1] * main->n[0]);
	return 0;
}

void polish_calculator(RPN *main)
{
	std::deque<std::string>::iterator it = main->deque.begin();
	std::deque<std::string>::iterator itend = main->deque.end();

	while(it != itend)
	{
		if(check_number((*it).c_str()))
		{
			main->n.push_front(std::atoi((*it).c_str()));
			//main->deque.erase(it);
		}
		else if(op((*it).c_str()[0]))
		{
			if(main->n.size() >= 2)
			{
				int result = operate(main, (*it).c_str()[0]);
				//main->deque.erase(it);
				main->n.pop_front(),main->n.pop_front();
				main->n.push_front(result);
			}
			else
				std::cerr << RED <<  "Error: Wrong input" << std::endl, exit(1);	
		}
		it++;
	}
	std::cout << GREEN << "Result = " << main->n[0] << std::endl;
}



int main(int argc, char **argv)
{
	if (argc != 2 || argv[1][0] == '\0')
		return (std::cerr << RED << "Error: Number of arguments\n"), 1;
	std::string input = argv[1];
	if(checkinit(input))
		return 1;
	RPN *main = new RPN;
	insert_input(main, input);
	if(!checkn(main) || !check_rown(main) || main->deque.size() <= 2 )
		return(1);
	print_dequestd(main);
	try
	{
		polish_calculator(main);
	}
	catch(std::exception & e)
	{
		std::cerr << e.what();
	}
	return 0;
}