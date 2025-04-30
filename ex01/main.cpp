/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:54:56 by jormoral          #+#    #+#             */
/*   Updated: 2025/04/30 18:52:38 by jormoral         ###   ########.fr       */
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
			return (std::cerr << "invalid character\n"), 1;
	}
	return 0;
}

void insert_input(RPN main, std::string input)
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
			main.deque.push_back(temp);
		}
	}
	/* std::deque<std::string>::iterator it = main.deque.begin();
	std::deque<std::string>::iterator itend = main.deque.end();
	while(it != itend)
	{
		std::cout << (*it) << std::endl;
		it++;
	} */
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (std::cerr << "Error: Number of arguments\n"), 1;
	std::string input = argv[1];
	if(checkinit(input))
		return 1;
	//std::cout << input << std::endl;
	RPN *main;
	/* insert_input(main, input);
	std::deque<std::string>::iterator it = main.deque.begin();
	std::deque<std::string>::iterator itend = main.deque.end();
	while(it != itend)
	{
		std::cout << (*it)<< std::endl;
		it++;
	} */
	return 0;
}